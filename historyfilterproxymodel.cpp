#include <QDateTime>

#include "historyfilterproxymodel.h"
#include "historymodel.h"


HistoryFilterProxyModel::HistoryFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);

    setSortRole(HistoryModel::CreatedAtRole);

    sort(0, Qt::DescendingOrder);

    connect(this, &QAbstractItemModel::rowsInserted, this, &HistoryFilterProxyModel::countChanged);
    connect(this, &QAbstractItemModel::rowsRemoved, this, &HistoryFilterProxyModel::countChanged);
    connect(this, &QAbstractItemModel::modelReset, this, &HistoryFilterProxyModel::countChanged);
    connect(this, &QAbstractItemModel::layoutChanged, this, &HistoryFilterProxyModel::countChanged);

}

QString HistoryFilterProxyModel::searchText() const
{
    return m_searchText;
}

void HistoryFilterProxyModel::setSearchText(const QString &searchText)
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

QString HistoryFilterProxyModel::actionFilter() const
{
    return m_actionFilter;
}

void HistoryFilterProxyModel::setActionFilter(const QString &actionFilter)
{
    QString normalizedFilter = actionFilter.trimmed().toLower();

    if(normalizedFilter != QStringLiteral("create") && normalizedFilter != QStringLiteral("increase")
        && normalizedFilter != QStringLiteral("decrease") && normalizedFilter != QStringLiteral("delete")
        && normalizedFilter != QStringLiteral("purchase") && normalizedFilter != QStringLiteral("sale")){
        normalizedFilter = QStringLiteral("all");
    }

    if(m_actionFilter == normalizedFilter)
        return;

    m_actionFilter = normalizedFilter;

    beginFilterChange();
    endFilterChange();

    emit actionFilterChanged();
    emit countChanged();

}

QDate HistoryFilterProxyModel::fromDate() const
{
    return m_fromDate;

}

void HistoryFilterProxyModel::setFromDate(const QDate &fromDate)
{
    if(m_fromDate == fromDate)
        return;

    m_fromDate = fromDate;

    beginFilterChange();
    endFilterChange();

    emit fromDateChanged();
    emit countChanged();

}

QDate HistoryFilterProxyModel::toDate() const
{
    return m_toDate;
}

void HistoryFilterProxyModel::setToDate(const QDate &toDate)
{
    if(m_toDate == toDate)
        return;

    m_toDate = toDate;

    beginFilterChange();
    endFilterChange();

    emit toDateChanged();
    emit countChanged();

}

int HistoryFilterProxyModel::count() const
{
    return rowCount();
}

void HistoryFilterProxyModel::sortNewestFirst()
{
    sort(0, Qt::DescendingOrder);
}

void HistoryFilterProxyModel::sortOldestFirst()
{
    sort(0, Qt::AscendingOrder);
}

bool HistoryFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if(!sourceModel())
        return false;

    const QModelIndex sourceIndex = sourceModel()->index(sourceRow, 0, sourceParent);

    const QString productName = sourceModel()->data(sourceIndex, HistoryModel::ProductNameRole).toString();

    const QString action = sourceModel()->data(sourceIndex, HistoryModel::ActionRole).toString().trimmed().toLower();

    const QString createdAt = sourceModel()->data(sourceIndex, HistoryModel::CreatedAtRole).toString();

    const QDate historyDate = QDateTime::fromString(createdAt, QStringLiteral("yyyy-MM-dd HH:mm:ss")).date();

    const bool matchesSearch = m_searchText.isEmpty() || productName.contains(m_searchText, Qt::CaseInsensitive);

    const bool matchesAction = m_actionFilter == QStringLiteral("all") || action == m_actionFilter;

    bool matchesDate = true;

    if(m_fromDate.isValid() && historyDate < m_fromDate){
        matchesDate = false;
    }

    if(m_toDate.isValid() && historyDate > m_toDate){
        matchesDate = false;
    }

    return matchesSearch && matchesAction && matchesDate;
}
