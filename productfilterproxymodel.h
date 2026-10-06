#ifndef PRODUCTFILTERPROXYMODEL_H
#define PRODUCTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QString>

class ProductFilterProxyModel : public QSortFilterProxyModel
{

    Q_OBJECT

    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText NOTIFY searchTextChanged)
    Q_PROPERTY(QString stockFilter READ stockFilter WRITE setStockFilter NOTIFY stockFilterChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QString categoryFilter READ categoryFilter WRITE setCategoryFIlter NOTIFY categoryFilterChanged)

public:
    explicit ProductFilterProxyModel(QObject *parent = nullptr);

    QString searchText() const;
    void setSearchText(const QString &searchText);

    QString stockFilter() const;
    void setStockFilter(const QString &stockFilter);

    int count() const;

    Q_INVOKABLE int sourceIndex(int proxyIndex) const;

    QString categoryFilter() const;
    void setCategoryFilter(const QString &categoryFilter);

signals:
    void searchTextChanged();
    void stockFilterChanged();
    void countChanged();
    void categoryFilterChanged();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    QString m_searchText;
    QString m_stockFilter = QStringLiteral("all");
    QString m_categoryFilter = QStringLiteral("all");

};

#endif // PRODUCTFILTERPROXYMODEL_H
