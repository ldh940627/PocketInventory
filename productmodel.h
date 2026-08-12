#ifndef PRODUCTMODEL_H
#define PRODUCTMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QVector>

struct Product
{
    int id = -1;
    QString name;
    int quantity = 0;
    int minimumQuantity = 0;

    int unitPrice = 0;
};

class ProductModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(int normalStockCount READ normalStockCount NOTIFY stockSummaryChanged)
    Q_PROPERTY(int lowStockCount READ lowStockCount NOTIFY stockSummaryChanged)

public:

    enum ProductRole
    {
        ProductIdRole = Qt::UserRole + 1,
        ProductNameRole,
        ProductQuantityRole,
        MinimumQuantityRole,
        UnitPriceRole
    };

    explicit ProductModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int count() const;

    Q_INVOKABLE QVariantMap get(int index) const;

    void setProducts(const QList<Product> &products);

    bool addProduct(int id, const QString &name, int quantity, int minimumQuantity, int unitPrice);

    bool setQuantity(int index, int quantity);

    Q_INVOKABLE bool increaseQuantity(int index);

    Q_INVOKABLE bool decreaseQuantity(int index);

    Q_INVOKABLE bool removeProduct(int index);

    Q_INVOKABLE bool containsProduct(const QString &name) const;

    int normalStockCount() const;

    int lowStockCount() const;

    qint64 totalInventoryValue() const;

    Product productAt(int index) const;


signals:
    void countChanged();
    void stockSummaryChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    bool isValidIndex(int index) const;
    QVector<Product> m_products;

};

#endif // PRODUCTMODEL_H
