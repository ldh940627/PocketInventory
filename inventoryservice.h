#ifndef INVENTORYSERVICE_H
#define INVENTORYSERVICE_H

#include <QSqlDatabase>
#include <QString>
#include <QVector>

#include "historyrepository.h"
#include "productmodel.h"
#include "productrepository.h"

class InventoryService
{
public:
    InventoryService(const QSqlDatabase &database, ProductRepository *productRepository, HistoryRepository *historyRepository);

    bool updateProduct(const Product &product, const QString &name, int minimumQuantity, int unitPrice, const QString &category, QString *errorMessage = nullptr);

    bool increaseQuantity(const Product &product, QString *errorMessage = nullptr);

    bool decreaseQuantity(const Product &product, QString *errorMessage = nullptr);

    bool deleteProduct(const Product &product, QString *errorMessage = nullptr);

    bool adjustQuantity(const Product &product, int delta, const QString &action, QString *errorMessage = nullptr);

    int addProduct(const QString &name, int quantity, int minimumQuantity, int unitPrice, const QString &category, QString *errorMessage = nullptr);

    bool importProduct(const QVector<Product> &products, QString *errorMessage = nullptr);
private:

    bool beginTransaction(QString *errorMessage);

    bool commitTransaction(QString *errorMessage);

    void rollbackTransaction();

    QSqlDatabase m_database;

    ProductRepository *m_productRepository = nullptr;
    HistoryRepository *m_historyRepository = nullptr;

};

#endif // INVENTORYSERVICE_H
