#ifndef HISTORYFILTERPROXYMODEL_H
#define HISTORYFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QString>
#include <QDate>

class HistoryFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(QString actionFilter READ actionFilter WRITE setActionFilter NOTIFY actionFilterChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText NOTIFY searchTextChanged)
    Q_PROPERTY(QDate fromDate READ fromDate WRITE setFromDate NOTIFY fromDateChanged)
    Q_PROPERTY(QDate toDate READ toDate WRITE setToDate NOTIFY toDateChanged)

public:
    explicit HistoryFilterProxyModel(QObject *parent = nullptr);

    QString searchText() const;
    void setSearchText(const QString &searchText);

    QString actionFilter() const;
    void setActionFilter(const QString &actionFilter);

    QDate fromDate() const;
    void setFromDate(const QDate &fromDate);

    QDate toDate() const;
    void setToDate(const QDate &toDate);

    int count() const;

    Q_INVOKABLE void sortNewestFirst();
    Q_INVOKABLE void sortOldestFirst();


signals:

    void countChanged();

    // 검색 관련
    void actionFilterChanged();
    void searchTextChanged();

    // 날짜 관련
    void fromDateChanged();
    void toDateChanged();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceparent) const override;

private:
    QString m_actionFilter = QStringLiteral("all");
    QString m_searchText;

    QDate m_fromDate;
    QDate m_toDate;
};

#endif // HISTORYFILTERPROXYMODEL_H
