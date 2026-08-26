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

    const QString sql = QStringLiteral("SELECT id, name, quantity, minimum_quantity, unit_price, category FROM products ORDER BY id ASC");

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
        product.unitPrice = query.value(4).toInt();
        product.category = query.value(5).toString();

        products.append(product);

    }

    if(errorMessage)
        errorMessage->clear();

    return products;
}

int ProductRepository::insertProduct(const QString &name, int quantity, int minimumQuantity, int unitPrice, const QString &category, QString *errorMessage) const
{
    if(!m_database.isOpen()){
        if(errorMessage){
            *errorMessage =
                QStringLiteral("데이터베이스가 열려 있지 않습니다.");
        }

        return -1;
    }

    QSqlQuery query(m_database);

    const QString sql = QStringLiteral("INSERT INTO products (name, quantity, minimum_quantity, unit_price, category) VALUES (?, ?, ?, ?, ?)");

    // ============================================================
    // Prepare
    // ============================================================

    if(!query.prepare(sql)){
        const QString error =
            query.lastError().text();

        qDebug()
            << "[ProductRepository] prepare 실패:"
            << error;

        if(errorMessage){
            *errorMessage = error;
        }

        return -1;
    }

    // ============================================================
    // Bind
    // ============================================================

    query.addBindValue(name.trimmed());

    query.addBindValue(quantity);

    query.addBindValue(minimumQuantity);

    query.addBindValue(unitPrice);

    query.addBindValue(category.trimmed());

    qDebug()
        << "[ProductRepository] INSERT 값:"
        << name
        << quantity
        << minimumQuantity
        << unitPrice << category;

    // ============================================================
    // Execute
    // ============================================================

    if(!query.exec()){
        const QString error =
            query.lastError().text();

        qDebug()
            << "[ProductRepository] exec 실패:"
            << error;

        if(errorMessage){
            *errorMessage = error;
        }

        return -1;
    }

    const int insertedId =
        query.lastInsertId().toInt();

    qDebug()
        << "[ProductRepository] INSERT 성공:"
        << insertedId;

    if(errorMessage){
        errorMessage->clear();
    }

    return insertedId;
}

bool ProductRepository::updateProductInfo(int productId, const QString &name, int minimumQuantity, int unitPrice, QString *errorMessage) const
{
    if(!m_database.isOpen()){
        if(errorMessage){
            *errorMessage = QStringLiteral("데이터베이스가 열려 있지 않습니다.");
        }

        return false;
    }

    QSqlQuery query(m_database);

    query.prepare(QStringLiteral(
        "UPDATE products "
        "SET "
        "name = :name, "
        "minimum_quantity = :minimum_quantity, "
        "unit_price = :unit_price, "
        "updated_at = CURRENT_TIMESTAMP "
        "WHERE id = :id"));

    query.bindValue(QStringLiteral(":name"), name.trimmed());
    query.bindValue(QStringLiteral(":minimum_quantity"), minimumQuantity);
    query.bindValue(QStringLiteral(":unit_price"), unitPrice);
    query.bindValue(QStringLiteral(":id"), productId);

    if(!query.exec()){
        if(errorMessage){
            *errorMessage = query.lastError().text();
        }

        qWarning() << "[productRepository::updateProductInfo]" << query.lastError().text();

        return false;
    }

    if(errorMessage){
        errorMessage->clear();
    }

    return true;
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


