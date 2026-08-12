#include "productmodel.h"

ProductModel::ProductModel(QObject *parent) : QAbstractListModel(parent)
{

}

int ProductModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return m_products.count();
}

QVariant ProductModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return {};

    if(index.row() < 0 || index.row() >= m_products.count())
    {
        return {};
    }

    const Product &product = m_products.at(index.row());

    switch(role){
    case ProductIdRole:
        return product.id;

    case ProductNameRole:
        return product.name;

    case ProductQuantityRole:
        return product.quantity;

    case MinimumQuantityRole:
        return product.minimumQuantity;

    case UnitPriceRole:
        return product.unitPrice;

    default:
        return {};
    }
}

int ProductModel::count() const
{
    return m_products.count();
}

QVariantMap ProductModel::get(int index) const
{
    if(!isValidIndex(index))
        return {};

    const Product &product = m_products.at(index);

    return {
        {
            QStringLiteral("productId"),
            product.id
        },
        {
            QStringLiteral("productName"),
            product.name
        },
        {
            QStringLiteral("productQuantity"),
            product.quantity
        },
        {
            QStringLiteral("minimumQuantity"),
            product.minimumQuantity
        },
        {
            QStringLiteral("unitPrice"),
            product.unitPrice
        }
    };
}

void ProductModel::setProducts(const QList<Product> &products)
{
    beginResetModel();

    m_products = QVector<Product>(products.begin(), products.end());
    endResetModel();

    emit countChanged();
    emit stockSummaryChanged();

}

bool ProductModel::addProduct(int id, const QString &name, int quantity, int minimumQuantity, int unitPrice)
{
    const QString normalizedName = name.trimmed();

    if(id<0)
        return false;
    if(normalizedName.isEmpty())
        return false;
    if(quantity < 0 || minimumQuantity < 0 || unitPrice < 0)
        return false;

    if(containsProduct(normalizedName))
        return false;

    const int newIndex = m_products.count();

    beginInsertRows(QModelIndex(), newIndex, newIndex);

    m_products.append({id, normalizedName, quantity, minimumQuantity, unitPrice});

    endInsertRows();

    emit countChanged();

    emit stockSummaryChanged();

    return true;
}

bool ProductModel::setQuantity(int index, int quantity)
{
    if(!isValidIndex(index))
        return false;

    if(quantity < 0)
        return false;

    Product &product = m_products[index];

    if(product.quantity == quantity)
        return true;

    product.quantity = quantity;

    const QModelIndex changedIndex = createIndex(index, 0);

    emit dataChanged(changedIndex, changedIndex, {ProductQuantityRole});

    emit stockSummaryChanged();

    return true;

}


bool ProductModel::increaseQuantity(int index)
{
    if (!isValidIndex(index))
        return false;

    Product &product = m_products[index];
    product.quantity++;

    const QModelIndex changedIndex = createIndex(index, 0);

    emit dataChanged(changedIndex, changedIndex,{ProductQuantityRole});
    emit stockSummaryChanged();

    return true;
}

bool ProductModel::decreaseQuantity(int index)
{
    if (!isValidIndex(index))
        return false;

    Product &product = m_products[index];

    if(product.quantity <= 0)
        return false;

    product.quantity--;

    const QModelIndex changedIndex = createIndex(index, 0);

    emit dataChanged(changedIndex, changedIndex, {ProductQuantityRole});
    emit stockSummaryChanged();

    return true;

}

bool ProductModel::removeProduct(int index)
{
    if (!isValidIndex(index))
        return false;

    beginRemoveRows(QModelIndex(),index,index);
    m_products.removeAt(index);
    endRemoveRows();
    emit countChanged();
    emit stockSummaryChanged();
    return true;

}

bool ProductModel::containsProduct(const QString &name) const
{
    const QString normalizedName = name.trimmed();

    for(const Product &product : m_products){
        if(product.name.compare(normalizedName, Qt::CaseInsensitive) == 0)
        {
            return true;
        }
    }

    return false;
}

int ProductModel::normalStockCount() const
{
    int normalCount = 0;

    for(const Product &product : m_products){
        if(product.quantity > product.minimumQuantity){
            ++normalCount;
        }
    }

    return normalCount;
}

int ProductModel::lowStockCount() const
{
    int lowCount = 0;

    for(const Product &product : m_products){
        if(product.quantity <= product.minimumQuantity){
            ++lowCount;
        }
    }

    return lowCount;
}

qint64 ProductModel::totalInventoryValue() const
{
    qint64 totalValue = 0;

    for(const Product &product : m_products){
        totalValue += static_cast<qint64>(product.quantity) * static_cast<qint64>(product.unitPrice);
    }

    return totalValue;

}

Product ProductModel::productAt(int index) const
{
    if(!isValidIndex(index))
        return {};

    return m_products.at(index);
}

QHash<int, QByteArray> ProductModel::roleNames() const
{
    return{
      {
        ProductIdRole,
        "productId"
      },
      {
        ProductNameRole,
        "productName"
      },
      {
        ProductQuantityRole,
        "productQuantity"
      },
      {
        MinimumQuantityRole,
        "minimumQuantity"
      },
      {
        UnitPriceRole,
        "unitPrice"
      }
    };
}

bool ProductModel::isValidIndex(int index) const
{
    return index >= 0 && index < m_products.count();
}