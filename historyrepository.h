#ifndef HISTORYREPOSITORY_H
#define HISTORYREPOSITORY_H

#include <QList>
#include <QSqlDatabase>
#include <QString>

#include "HistoryRecord.h"


class HistoryRepository
{


public:

    explicit HistoryRepository(const QSqlDatabase &database);

    bool insertHistory(int productId, const QString &productName, int oldQuantity, int newQuantity, const QString &action, QString *errorMessage = nullptr) const;

    QList<HistoryRecord> loadAll(QString *errorMessage = nullptr) const;

private:
    QSqlDatabase m_database;

};

#endif // HISTORYREPOSITORY_H
