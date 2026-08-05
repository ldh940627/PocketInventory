#include "historyrepository.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>


HistoryRepository::HistoryRepository(const QSqlDatabase &database) : m_database(database)
{

}

bool HistoryRepository::insertHistory(int productId, const QString &productName, int oldQuantity, int newQuantity, const QString &action, QString *errorMessage) const
{
    if(!m_database.isOpen()){
        if(errorMessage){
            *errorMessage = QStringLiteral("데이터베이스가 열려 있지 않습니다.");
        }

        return false;
    }

    QSqlQuery query(m_database);

    query.prepare(QStringLiteral( "INSERT INTO history ("
                                 "product_id, "
                                 "product_name, "
                                 "old_quantity, "
                                 "new_quantity, "
                                 "action"
                                 ") "
                                 "VALUES ("
                                 ":product_id, "
                                 ":product_name, "
                                 ":old_quantity, "
                                 ":new_quantity, "
                                 ":action"
                                 ")"));

    query.bindValue(QStringLiteral(":product_id"), productId);
    query.bindValue(QStringLiteral(":product_name"), productName.trimmed());
    query.bindValue(QStringLiteral(":old_quantity"), oldQuantity);
    query.bindValue(QStringLiteral(":new_quantity"),newQuantity);
    query.bindValue(QStringLiteral(":action"), action.trimmed().toUpper());

    if(!query.exec()){
        if(errorMessage){
            *errorMessage = query.lastError().text();
        }

        return false;
    }

    if(errorMessage)
        errorMessage->clear();

    return true;
}

QList<HistoryRecord> HistoryRepository::loadAll(QString *errorMessage) const
{
    QList<HistoryRecord> historyRecords;

    if(!m_database.isOpen()){
        if(errorMessage){
            *errorMessage = QStringLiteral("데이터베이스가 열려 있지 않습니다.");
        }
        return historyRecords;
    }

    QSqlQuery query(m_database);

    const QString sql = QStringLiteral("SELECT "
                                       "id, "
                                       "product_id, "
                                       "product_name, "
                                       "old_quantity, "
                                       "new_quantity, "
                                       "action, "
                                       "created_at "
                                       "FROM history "
                                       "ORDER BY id DESC");

    if(!query.exec(sql)){
        if(errorMessage){
            *errorMessage = query.lastError().text();
        }

        return historyRecords;
    }

    while(query.next()){
        HistoryRecord record;

        record.id = query.value(0).toInt();
        record.productId = query.value(1).toInt();
        record.productName = query.value(2).toString();
        record.oldQuantity = query.value(3).toInt();
        record.newQuantity = query.value(4).toInt();
        record.action = query.value(5).toString();
        record.createdAt = query.value(6).toString();

        historyRecords.append(record);
    }

    if(errorMessage)
        errorMessage->clear();

    return historyRecords;
}
