#include "productfilterproxymodel.h"

#include "productmodel.h"

ProductFilterProxyModel::ProductFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
    connect(this, &QAbstractItemModel::rowsInserted, this, &ProductFilterProxyModel::countChanged);
    connect(this, &QAbstractItemModel::rowsRemoved, this, &ProductFilterProxyModel::countChanged);
    connect(this, &QAbstractItemModel::layoutChanged, this, &ProductFilterProxyModel::countChanged);
    connect(this, &QAbstractItemModel::modelReset, this, &ProductFilterProxyModel::countChanged);
}

QString ProductFilterProxyModel::searchText() const
{
    return m_searchText;
}

void ProductFilterProxyModel::setSearchText(const QString &searchText)
{
    const QString normalizedText = searchText.trimmed();
    if(m_searchText == normalizedText)
        return;

    m_searchText = normalizedText;

    beginFilterChange();
    endFilterChange();

    emit searchTextChanged();
    emit countChanged();

}

QString ProductFilterProxyModel::stockFilter() const
{
    return m_stockFilter;
}

void ProductFilterProxyModel::setStockFilter(const QString &stockFilter)
{
    QString normalizedFilter = stockFilter.trimmed().toLower();

    if(normalizedFilter != QStringLiteral("normal") && normalizedFilter != QStringLiteral("low")){
        normalizedFilter = QStringLiteral("all");
    }

    if(m_stockFilter == normalizedFilter)
        return;

    m_stockFilter = normalizedFilter;

    beginFilterChange();
    endFilterChange();

    emit stockFilterChanged();
    emit countChanged();

}

int ProductFilterProxyModel::count() const
{
    return rowCount();
}

int ProductFilterProxyModel::sourceIndex(int proxyIndex) const
{
    if(proxyIndex < 0 || proxyIndex >= rowCount())
        return -1;

    const QModelIndex proxyModelIndex = index(proxyIndex, 0);
    const QModelIndex sourceModelIndex = mapToSource(proxyModelIndex);
    return sourceModelIndex.row();
}

bool ProductFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if(!sourceModel())
        return false;

    const QModelIndex sourceIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    const QString productName = sourceModel()->data(sourceIndex, ProductModel::ProductNameRole).toString();
    const int productQuantity = sourceModel()->data(sourceIndex, ProductModel::ProductQuantityRole).toInt();
    const int minimumQuantity = sourceModel()->data(sourceIndex, ProductModel::MinimumQuantityRole).toInt();
    const bool matchesSearch = m_searchText.isEmpty() || productName.contains(m_searchText, Qt::CaseInsensitive);

    qDebug()
        << m_stockFilter
        << productName
        << productQuantity
        << minimumQuantity;

    bool matchesStock = true;

    if(m_stockFilter == QStringLiteral("normal")){
        matchesStock = productQuantity > minimumQuantity;
    }
    else if (m_stockFilter == QStringLiteral("low")){
        matchesStock = productQuantity <= minimumQuantity;
    }
    return matchesSearch && matchesStock;
}


