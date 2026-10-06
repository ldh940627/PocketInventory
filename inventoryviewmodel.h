#ifndef INVENTORYVIEWMODEL_H
#define INVENTORYVIEWMODEL_H

#include <QAbstractItemModel>
#include <QObject>
#include <QString>
#include <QUrl>

#include "productfilterproxymodel.h"
#include "productmodel.h"
#include "productrepository.h"
#include "inventoryservice.h"
#include "service/csvservice.h"

class InventoryViewModel : public QObject
{
    Q_OBJECT

    // listview가 사용할 필터링된 모델
    Q_PROPERTY(QAbstractItemModel* products READ products CONSTANT)

    Q_PROPERTY(QAbstractItemModel* lowStockProducts READ lowStockProducts CONSTANT)

    // 통계 카드
    Q_PROPERTY(int totalCount READ totalCount NOTIFY stockSummaryChanged)

    Q_PROPERTY(int normalStockCount READ normalStockCount NOTIFY stockSummaryChanged)

    Q_PROPERTY(int lowStockCount READ lowStockCount NOTIFY stockSummaryChanged)

    Q_PROPERTY(qint64 totalInventoryValue READ totalInventoryValue NOTIFY stockSummaryChanged)

    // 검색 결과 개수
    Q_PROPERTY(int filteredCount READ filteredCount NOTIFY filteredCountChanged)

    // 검색어
    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText NOTIFY searchTextChanged)

    // 재고 상태 필터
    Q_PROPERTY(QString stockFilter READ stockFilter WRITE setStockFilter NOTIFY stockFilterChanged)

    // 카테고리
    Q_PROPERTY(QStringList categories READ categories NOTIFY categoriesChanged)

    Q_PROPERTY(QString categoryFilter READ categoryFilter WRITE setCategoryFilter NOTIFY categoryFilterChanged)

    Q_PROPERTY(QVariantList categorySummary READ categorySummary NOTIFY categorySummaryChanged)
public:

    explicit InventoryViewModel(ProductRepository *productRepository, InventoryService *inventoryService, QObject *parent = nullptr);

    QAbstractItemModel *products();

    QAbstractItemModel *lowStockProducts();

    int totalCount() const;

    int normalStockCount() const;

    int lowStockCount() const;

    qint64 totalInventoryValue() const;

    int filteredCount() const;

    QString searchText() const;

    void setSearchText(const QString &searchText);

    QString stockFilter() const;

    void setStockFilter(const QString &stockFilter);

    QStringList categories() const;
    QString categoryFilter() const;
    void setCategoryFilter(const QString &filter);

    QVariantList categorySummary() const;

    Q_INVOKABLE bool addProduct(const QString &productNameText, const QString &productQuantityText, const QString &minimumQuantityText, const QString &unitPriceText, const QString &categoryText);
    Q_INVOKABLE bool updateProduct(int proxyIndex, const QString &productNameText, const QString &minimumQuantityText, const QString &unitPriceText, const QString &categoryText);
    Q_INVOKABLE bool receiveStock(int proxyIndex, const QString &quantityText);
    Q_INVOKABLE bool releaseStock(int proxyIndex, const QString &quantityText);
    Q_INVOKABLE void increaseQuantity(int proxyIndex);
    Q_INVOKABLE void decreaseQuantity(int proxyIndex);
    Q_INVOKABLE void removeProduct(int proxyIndex);
    Q_INVOKABLE void resetFilters();
    Q_INVOKABLE bool exportProducts(const QUrl &fileUrl);
    Q_INVOKABLE bool importProducts(const QUrl &fileUrl);


signals:
    void stockSummaryChanged();

    void filteredCountChanged();

    void searchTextChanged();

    void stockFilterChanged();

    void messageRequested(const QString &message, const QString &colorName);

    void historyChanged();

    void categoriesChanged();

    void categoryFilterChanged();

    void categorySummaryChanged();

private:
    int toSourceIndex(int proxyIndex) const;

    ProductRepository *m_productRepository = nullptr;
    InventoryService *m_inventoryService = nullptr;

    ProductModel m_productModel;
    ProductFilterProxyModel m_filterModel;
    ProductFilterProxyModel m_lowStockModel;
    csvservice m_csvService;


};

#endif // INVENTORYVIEWMODEL_H
