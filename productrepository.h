#ifndef PRODUCTREPOSITORY_H
#define PRODUCTREPOSITORY_H

#include <QList>
#include <QSqlDatabase>
#include <QString>

#include "productmodel.h"

class ProductRepository
{
public:
    explicit ProductRepository(const QSqlDatabase &database);

    QList<Product> loadAll(QString *errorMessage = nullptr) const;

    int insertProduct(const QString &name, int quantity, int minimumQuantity, int unitPrice, QString *errorMessage = nullptr) const;

    bool updateProductInfo(int productId, const QString &name, int minimumQuantity, int unitPrice, QString *errorMessage = nullptr) const;

    bool updateQuantity(int productId, int quantity, QString *errorMessage = nullptr) const;

    bool deleteProduct(int productId, QString *errorMessage = nullptr) const;


private:
    QSqlDatabase m_database;
};

#endif // PRODUCTREPOSITORY_H
