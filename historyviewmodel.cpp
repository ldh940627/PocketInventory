#include "historyviewmodel.h"

#include <QDebug>
#include <QDate>

HistoryViewModel::HistoryViewModel(HistoryRepository *repository, QObject *parent) : QObject(parent), m_repository(repository)
{
    m_filterModel.setSourceModel(&m_historyModel);

    connect(&m_historyModel, &HistoryModel::countChanged, this, &HistoryViewModel::totalCountChanged);

    connect(&m_filterModel, &HistoryFilterProxyModel::countChanged, this, &HistoryViewModel::countChanged);
    connect(&m_filterModel, &HistoryFilterProxyModel::actionFilterChanged, this, &HistoryViewModel::actionFilterChanged);
    connect(&m_filterModel, &HistoryFilterProxyModel::searchTextChanged, this, &HistoryViewModel::searchTextChanged);

    connect(&m_filterModel, &HistoryFilterProxyModel::fromDateChanged, this, &HistoryViewModel::fromDateChanged);
    connect(&m_filterModel, &HistoryFilterProxyModel::toDateChanged, this, &HistoryViewModel::toDateChanged);
    reload();
}

QAbstractItemModel *HistoryViewModel::history()
{
    return &m_filterModel;
}

QAbstractItemModel *HistoryViewModel::recentHistory()
{
    return &m_historyModel;

}

int HistoryViewModel::count() const
{
    return m_filterModel.count();
}

int HistoryViewModel::totalCount() const
{
    return m_filterModel.count();
}

QString HistoryViewModel::searchText() const
{
    return m_filterModel.searchText();
}

void HistoryViewModel::setSearchText(const QString &searchText)
{
    m_filterModel.setSearchText(searchText);
}

QString HistoryViewModel::actionFilter() const
{
    return m_filterModel.actionFilter();
}

void HistoryViewModel::setActionFilter(const QString &actionFilter)
{
    m_filterModel.setActionFilter(actionFilter);
}

QDate HistoryViewModel::fromDate() const
{
    return m_filterModel.fromDate();
}

void HistoryViewModel::setFromDate(const QDate &fromDate)
{
    m_filterModel.setFromDate(fromDate);
}

QDate HistoryViewModel::toDate() const
{
    return m_filterModel.toDate();
}

void HistoryViewModel::setToDate(const QDate &toDate)
{
    m_filterModel.setToDate(toDate);
}

QString HistoryViewModel::datePreset() const
{
    return m_datePreset;
}

QString HistoryViewModel::sortOrder() const
{
    return m_sortOrder;
}

void HistoryViewModel::reload()
{
    if(!m_repository){
        qWarning() << "HistoryRepository가 연결되지 않았습니다.";

        return;
    }

    QString errorMessage;

    const QList<HistoryRecord> records = m_repository->loadAll(&errorMessage);

    if(!errorMessage.isEmpty()){
        qWarning() << "재고 이력 불러오기 실패:" << errorMessage;

        return;
    }

    m_historyModel.setHistory(records);

}

void HistoryViewModel::resetFilters()
{
    setSearchText(QString());
    setActionFilter(QStringLiteral("all"));

    showAllDates();
    sortNewestFirst();
}

void HistoryViewModel::setDateRange(const QString &fromDateText, const QString &toDateText)
{
    const QDate fromDate = QDate::fromString(fromDateText.trimmed(), QStringLiteral("yyyy-MM-dd"));
    const QDate toDate = QDate::fromString(toDateText.trimmed(), QStringLiteral("yyyy-MM-dd"));

    setFromDate(fromDate);
    setToDate(toDate);

    if(m_datePreset != QStringLiteral("custom")){
        m_datePreset = QStringLiteral("custom");
        emit datePresetChanged();
    }
}

void HistoryViewModel::sortNewestFirst()
{
    m_filterModel.sortNewestFirst();

    if(m_sortOrder != QStringLiteral("newest")){
        m_sortOrder = QStringLiteral("newest");
        emit sortOrderChanged();
    }
}

void HistoryViewModel::sortOldestFirst()
{
    m_filterModel.sortOldestFirst();

    if(m_sortOrder != QStringLiteral("oldest")){
        m_sortOrder = QStringLiteral("oldest");
        emit sortOrderChanged();
    }
}

void HistoryViewModel::showAllDates()
{
    setFromDate(QDate());
    setToDate(QDate());

    if(m_datePreset != QStringLiteral("all")){
        m_datePreset = QStringLiteral("all");
        emit datePresetChanged();
    }
}

void HistoryViewModel::showToday()
{
    const QDate today = QDate::currentDate();

    setFromDate(today);
    setToDate(today);

    if(m_datePreset != QStringLiteral("today")){
        m_datePreset = QStringLiteral("today");
        emit datePresetChanged();
    }
}

void HistoryViewModel::showLast7Days()
{
    const QDate today = QDate::currentDate();

    setFromDate(today.addDays(-6));
    setToDate(today);

    if(m_datePreset != QStringLiteral("7days")){
        m_datePreset = QStringLiteral("7days");
        emit datePresetChanged();
    }
}

void HistoryViewModel::showLast30Days()
{
    const QDate today = QDate::currentDate();

    setFromDate(today.addDays(-29));
    setToDate(today);

    if(m_datePreset != QStringLiteral("30days")){
        m_datePreset = QStringLiteral("30days");
        emit datePresetChanged();
    }
}
