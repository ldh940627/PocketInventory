#ifndef PRODUCTMODEL_H
#define PRODUCTMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QVector>

struct Product
{
    QString name;
    int quantity = 0;
    int minimumQuantity = 0;
};

class ProductModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(
        int count
        READ count
        NOTIFY countChanged)

    Q_PROPERTY(int normalStockCount READ normalStockCount NOTIFY stockSummaryChanged)
    Q_PROPERTY(int lowStockCount READ lowStockCount NOTIFY stockSummaryChanged)

public:


    enum ProductRole
    {
        ProductNameRole = Qt::UserRole + 1,
        ProductQuantityRole,
        MinimumQuantityRole
    };

    explicit ProductModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int count() const;

    Q_INVOKABLE QVariantMap get(int index) const;

    Q_INVOKABLE bool addProduct(
        const QString &name,
        int quantity,
        int minimumQuantity);

    Q_INVOKABLE bool increaseQuantity(int index);
    Q_INVOKABLE bool decreaseQuantity(int index);
    Q_INVOKABLE bool removeProduct(int index);

    Q_INVOKABLE bool containsProduct(const QString &name) const;

    int normalStockCount() const;
    int lowStockCount() const;


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
