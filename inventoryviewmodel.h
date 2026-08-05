#ifndef INVENTORYVIEWMODEL_H
#define INVENTORYVIEWMODEL_H

#include <QAbstractItemModel>
#include <QObject>
#include <QString>

#include "productfilterproxymodel.h"
#include "productmodel.h"
#include "productrepository.h"
#include "historyrepository.h"

class InventoryViewModel : public QObject
{
    Q_OBJECT

    // listview가 사용할 필터링된 모델
    Q_PROPERTY(QAbstractItemModel* products READ products CONSTANT)

    // 통계 카드
    Q_PROPERTY(int totalCount READ totalCount NOTIFY stockSummaryChanged)
    Q_PROPERTY(int normalStockCount READ normalStockCount NOTIFY stockSummaryChanged)
    Q_PROPERTY(int lowStockCount READ lowStockCount NOTIFY stockSummaryChanged)

    // 검색 결과 개수
    Q_PROPERTY(int filteredCount READ filteredCount NOTIFY filteredCountChanged)

    // 검색어
    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText NOTIFY searchTextChanged)

    // 재고 상태 필터
    Q_PROPERTY(QString stockFilter READ stockFilter WRITE setStockFilter NOTIFY stockFilterChanged)


public:
    explicit InventoryViewModel(ProductRepository *productRepository, HistoryRepository *historyRepository, QObject *parent = nullptr);

    QAbstractItemModel *products();

    int totalCount() const;
    int normalStockCount() const;
    int lowStockCount() const;
    int filteredCount() const;

    QString searchText() const;
    void setSearchText(const QString &searchText);

    QString stockFilter() const;
    void setStockFilter(const QString &stockFilter);

    Q_INVOKABLE bool addProduct(const QString &productNameText, const QString &productQuantityText, const QString &minimumQuantityText);
    Q_INVOKABLE void increaseQuantity(int proxyIndex);
    Q_INVOKABLE void decreaseQuantity(int proxyIndex);
    Q_INVOKABLE void removeProduct(int proxyIndex);
    Q_INVOKABLE void resetFilters();



signals:
    void stockSummaryChanged();
    void filteredCountChanged();

    void searchTextChanged();
    void stockFilterChanged();

    void messageRequested(const QString &message, const QString &colorName);

private:
    int toSourceIndex(int proxyIndex) const;

    ProductRepository *m_productRepository = nullptr;
    HistoryRepository *m_historyRepository = nullptr;

    ProductModel m_productModel;
    ProductFilterProxyModel m_filterModel;


};

#endif // INVENTORYVIEWMODEL_H
