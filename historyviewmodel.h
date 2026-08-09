#ifndef HISTORYVIEWMODEL_H
#define HISTORYVIEWMODEL_H

#include <QAbstractItemModel>
#include <QObject>

#include "historyfilterproxymodel.h"
#include "historymodel.h"
#include "historyrepository.h"

class HistoryViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QAbstractItemModel* history READ history CONSTANT)

    Q_PROPERTY(int count READ count NOTIFY countChanged)

    Q_PROPERTY(QString actionFilter READ actionFilter WRITE setActionFilter NOTIFY actionFilterChanged)

    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText NOTIFY searchTextChanged)

    Q_PROPERTY(QDate fromDate READ fromDate WRITE setFromDate NOTIFY fromDateChanged)

    Q_PROPERTY(QDate toDate READ toDate WRITE setToDate NOTIFY toDateChanged)

    Q_PROPERTY(QString datePreset READ datePreset NOTIFY datePresetChanged)

    Q_PROPERTY(QString sortOrder READ sortOrder NOTIFY sortOrderChanged)
public:
    explicit HistoryViewModel(HistoryRepository *repository, QObject *parent = nullptr);

    QAbstractItemModel *history();

    int count() const;

    QString searchText() const;
    void setSearchText(const QString &searchText);

    QString actionFilter() const;
    void setActionFilter(const QString &actionFilter);

    QDate fromDate() const;
    void setFromDate(const QDate &fromDate);

    QDate toDate() const;
    void setToDate(const QDate &toDate);

    QString datePreset() const;
    QString sortOrder() const;

    Q_INVOKABLE void reload();
    Q_INVOKABLE void resetFilters();

    Q_INVOKABLE void setDateRange(const QString &fromDateText, const QString &toDateText);

    Q_INVOKABLE void sortNewestFirst();
    Q_INVOKABLE void sortOldestFirst();

    Q_INVOKABLE void showAllDates();
    Q_INVOKABLE void showToday();
    Q_INVOKABLE void showLast7Days();
    Q_INVOKABLE void showLast30Days();


signals:
    void countChanged();
    void actionFilterChanged();
    void searchTextChanged();

    void fromDateChanged();
    void toDateChanged();

    void datePresetChanged();
    void sortOrderChanged();

private:
    HistoryRepository *m_repository = nullptr;
    HistoryModel m_historyModel;
    HistoryFilterProxyModel m_filterModel;

    QString m_datePreset = QStringLiteral("all");
    QString m_sortOrder = QStringLiteral("newest");

};

#endif // HISTORYVIEWMODEL_H
