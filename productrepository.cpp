#include "productrepository.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

ProductRepository::ProductRepository(const QSqlDatabase &database) : m_database(database)
{

}

QList<Product> ProductRepository::loadAll(QString *errorMessage) const
{
    QList<Product> products;

    if(!m_database.isOpen()){
        if(errorMessage){
            *errorMessage = QStringLiteral("데이터베이스가 열려 있지 않습니다.");
        }
        return products;
    }

    QSqlQuery query(m_database);

    const QString sql = QStringLiteral(  "SELECT "
                                       "id, "
                                       "name, "
                                       "quantity, "
                                       "minimum_quantity "
                                       "FROM products "
                                       "ORDER BY id ASC");

    if(!query.exec(sql)){
        if(errorMessage){
            *errorMessage = query.lastError().text();
        }
        return products;
    }

    while(query.next()){
        Product product;

        product.id = query.value(0).toInt();
        product.name = query.value(1).toString();
        product.quantity = query.value(2).toInt();
        product.minimumQuantity = query.value(3).toInt();

        products.append(product);

    }

    if(errorMessage)
        errorMessage->clear();

    return products;
}

int ProductRepository::insertProduct(const QString &name, int quantity, int minimumQuantity, QString *errorMessage) const
{
    if(!m_database.isOpen()){
        if(errorMessage){
            *errorMessage = QStringLiteral("데이터베이스가 열려 있지 않습니다.");
        }

        return -1;
    }

    QSqlQuery query(m_database);

    query.prepare(QStringLiteral("INSERT INTO products ("
                                 "name, "
                                 "quantity, "
                                 "minimum_quantity"
                                 ") "
                                 "VALUES ("
                                 ":name, "
                                 ":quantity, "
                                 ":minimum_quantity"
                                 ")"));

    query.bindValue(QStringLiteral(":name"), name.trimmed());
    query.bindValue(QStringLiteral(":quantity"), quantity);
    query.bindValue(QStringLiteral(":minimum_quantity"), minimumQuantity);

    if(!query.exec()){
        if(errorMessage){
            *errorMessage = query.lastError().text();
        }

        return -1;
    }

    const int insertedId = query.lastInsertId().toInt();

    if(errorMessage)
        errorMessage->clear();

    return insertedId;
}

bool ProductRepository::updateQuantity(int productId, int quantity, QString *errorMessage) const
{
    QSqlQuery query(m_database);

    query.prepare( "UPDATE products "
                  "SET quantity = :quantity, "
                  "updated_at = CURRENT_TIMESTAMP "
                  "WHERE id = :id");

    query.bindValue(":quantity", quantity);
    query.bindValue(":id", productId);

    if(!query.exec())
    {
        if(errorMessage)
            *errorMessage = query.lastError().text();
        return false;
    }

    return true;
}

bool ProductRepository::deleteProduct(int productId, QString *errorMessage) const
{
    QSqlQuery query(m_database);

    query.prepare( "DELETE FROM products "
                  "WHERE id = :id");

    query.bindValue(":id", productId);

    if(!query.exec())
    {
        if(errorMessage)
            *errorMessage = query.lastError().text();
        return false;
    }

    return true;

}


