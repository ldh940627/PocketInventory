#include "inventoryviewmodel.h"
#include <QDebug>


InventoryViewModel::InventoryViewModel(ProductRepository *productrepository, InventoryService *inventoryService, QObject *parent)
    : QObject(parent), m_productRepository(productrepository), m_inventoryService(inventoryService)
{
    m_filterModel.setSourceModel(&m_productModel);

    m_lowStockModel.setSourceModel(&m_productModel);

    m_lowStockModel.setStockFilter(QStringLiteral("low"));

    connect(&m_productModel, &ProductModel::countChanged, this, &InventoryViewModel::stockSummaryChanged);
    connect(&m_productModel, &ProductModel::stockSummaryChanged, this, &InventoryViewModel::stockSummaryChanged);
    connect(&m_filterModel, &ProductFilterProxyModel::countChanged, this, &InventoryViewModel::filteredCountChanged);
    connect(&m_filterModel, &ProductFilterProxyModel::searchTextChanged, this, &InventoryViewModel::searchTextChanged);
    connect(&m_filterModel, &ProductFilterProxyModel::stockFilterChanged, this, &InventoryViewModel::stockFilterChanged);

    if(!m_productRepository){
        emit messageRequested(QStringLiteral("상품저장소가 연결 되지 않았습니다."), QStringLiteral("red"));
        return;

    }

    QString errorMessage;

    const QList<Product> products = m_productRepository->loadAll(&errorMessage);

    if(!errorMessage.isEmpty()){
        qWarning() << "상품 불러오기 실패:" << errorMessage;

        return;
    }

    m_productModel.setProducts(products);

}

QAbstractItemModel *InventoryViewModel::products()
{
    return &m_filterModel;
}

QAbstractItemModel *InventoryViewModel::lowStockProducts()
{
    return &m_lowStockModel;
}

int InventoryViewModel::totalCount() const
{
    return m_productModel.count();
}

int InventoryViewModel::normalStockCount() const
{
    return m_productModel.normalStockCount();
}

int InventoryViewModel::lowStockCount() const
{
    return m_productModel.lowStockCount();
}

int InventoryViewModel::filteredCount() const
{
    return m_filterModel.count();
}

QString InventoryViewModel::searchText() const
{
    return m_filterModel.searchText();
}

void InventoryViewModel::setSearchText(const QString &searchText)
{
    m_filterModel.setSearchText(searchText);
}

QString InventoryViewModel::stockFilter() const
{
    return m_filterModel.stockFilter();
}

void InventoryViewModel::setStockFilter(const QString &stockFilter)
{
    m_filterModel.setStockFilter(stockFilter);
}

bool InventoryViewModel::addProduct(const QString &productNameText, const QString &productQuantityText, const QString &minimumQuantityText)
{

    const QString productName = productNameText.trimmed();
    const QString quantityText = productQuantityText.trimmed();
    const QString minimumText = minimumQuantityText.trimmed();

    if(productName.isEmpty()){
        emit messageRequested(QStringLiteral("상품명을 입력해주세요."), QStringLiteral("red"));
        return false;
    }

    if(quantityText.isEmpty()){
        emit messageRequested(QStringLiteral("현재 수량을 입력해주세요. "), QStringLiteral("red"));
        return false;
    }

    if(minimumText.isEmpty()){
        emit messageRequested(QStringLiteral("최소 수량을 입력해주세요."), QStringLiteral("red"));
        return false;
    }

    bool quantityOk = false;
    bool minimumOk = false;

    const int quantity = quantityText.toInt(&quantityOk);
    const int minimumQuantity = minimumText.toInt(&minimumOk);

    if(!quantityOk || quantity < 0){
        emit messageRequested(QStringLiteral("현재 수량은 0 이상의 정수여야 합니다."), QStringLiteral("red"));
        return false;
    }

    if(!minimumOk || minimumQuantity < 0){
        emit messageRequested(QStringLiteral("최소 수량은 0 이상의 정수여야 합니다."), QStringLiteral("red"));
        return false;
    }

    if(m_productModel.containsProduct(productName)){
        emit messageRequested(productName + QStringLiteral("상품은 이미 등록되어 있습니다."), QStringLiteral("red"));
        return false;
    }

    if(!m_productRepository){
        emit messageRequested(QStringLiteral("상품 저장소가 연결되지 않았습니다."), QStringLiteral("red"));
        return false;
    }

    QString errorMessage;

    const int productId = m_inventoryService->addProduct(productName, quantity, minimumQuantity, &errorMessage);

    if(productId < 0){
        emit messageRequested(QStringLiteral("상품을 저장하지 못했습니다: ") + errorMessage, QStringLiteral("red"));
        return false;
    }

    if(!m_productModel.addProduct(productId, productName, quantity, minimumQuantity)){
        emit messageRequested(QStringLiteral("상품은 DB에 저장됐지만 " "화면 모델 갱신에 실패했습니다."), QStringLiteral("red"));
        return false;
    }

    emit historyChanged();

    emit messageRequested(productName + QStringLiteral(" 상품이 등록되었습니다."), QStringLiteral("green"));

    return true;
}

bool InventoryViewModel::receiveStock(int proxyIndex, const QString &quantityText)
{
    const int sourceIndex = toSourceIndex(proxyIndex);

    if(sourceIndex < 0){
        emit messageRequested(QStringLiteral("상품 위치를 찾을 수 없습니다."), QStringLiteral("red"));
        return false;
    }

    bool quantityOk = false;

    const int amount = quantityText.trimmed().toInt(&quantityOk);

    if(!quantityOk || amount <= 0){
        emit messageRequested(QStringLiteral("입고 수량은 1 이상의 정수여야 합니다."), QStringLiteral("red"));

        return false;
    }

    const Product product = m_productModel.productAt(sourceIndex);

    QString errorMessage;

    if(!m_inventoryService->adjustQuantity(product, amount, QString("PURCHASE"), &errorMessage)){
        emit messageRequested(QStringLiteral("입고 처리에 실패했습니다:") + errorMessage, QStringLiteral("red"));
        return false;
    }

    const int newQuantity = product.quantity + amount;

    m_productModel.setQuantity(sourceIndex, newQuantity);

    emit historyChanged();

    emit messageRequested(product.name + QStringLiteral("") + QString::number(amount) + QStringLiteral("개 입고 처리했습니다."),
                          QStringLiteral("green"));

    return true;

}

bool InventoryViewModel::releaseStock(int proxyIndex, const QString &quantityText)
{
    const int sourceIndex = toSourceIndex(proxyIndex);

    if(sourceIndex < 0){
        emit messageRequested(QStringLiteral("상품 위치를 찾을 수 없습니다."), QStringLiteral("red"));
        return false;
    }

    bool quantityOk = false;

    const int amount = quantityText.trimmed().toInt(&quantityOk);

    if(!quantityOk || amount <= 0){
        emit messageRequested(QStringLiteral("출고 수량은 1이상의 정수여야 합니다."),
                             QStringLiteral("red"));

        return false;
    }

    const Product product = m_productModel.productAt(sourceIndex);

    if(product.quantity < amount){
        emit messageRequested(QStringLiteral("출고 수량이 현재 재고보다 많습니다."), QStringLiteral("red"));
        return false;
    }

    QString errorMessage;

    if(!m_inventoryService->adjustQuantity(product, -amount, QStringLiteral("SALE"), &errorMessage)){
        emit messageRequested(QStringLiteral("출고 처리에 실패했습니다: ") + errorMessage,
                              QStringLiteral("red"));
        return false;
    }

    const int newQuantity = product.quantity - amount;

    m_productModel.setQuantity(sourceIndex, newQuantity);

    emit historyChanged();

    emit messageRequested(product.name + QStringLiteral(" ") + QString::number(amount)
                              +QStringLiteral("개 출고 처리했습니다."), QStringLiteral("darkorange"));
    return true;

}

void InventoryViewModel::increaseQuantity(int proxyIndex)
{
    const int sourceIndex = toSourceIndex(proxyIndex);

    if(sourceIndex < 0){
        emit messageRequested(QStringLiteral("상품 위치를 찾을 수 없습니다."), QStringLiteral("red"));
        return;
    }

    const Product product = m_productModel.productAt(sourceIndex);

    QString errorMessage;

    if(!m_inventoryService->increaseQuantity(product, &errorMessage)){
         emit messageRequested(QStringLiteral("수량 변경에 실패했습니다."), QStringLiteral("red"));
        return;
    }

    m_productModel.increaseQuantity(sourceIndex);

    emit historyChanged();

    emit messageRequested(
        product.name
            + QStringLiteral(" 수량을 ")
            + QString::number(product.quantity + 1)
            + QStringLiteral( "개로 변경했습니다." ), QStringLiteral("green"));
}

void InventoryViewModel::decreaseQuantity(int proxyIndex)
{
    const int sourceIndex = toSourceIndex(proxyIndex);

    if(sourceIndex < 0){
        emit messageRequested(QStringLiteral("상품 위치를 찾을 수 없습니다."), QStringLiteral("red"));
        return;
    }

    const Product product = m_productModel.productAt(sourceIndex);

    QString errorMessage;

    if (product.quantity <= 0) {
        emit messageRequested(QStringLiteral("재고는 0개보다 작을 수 없습니다."), QStringLiteral("red"));

        return;
    }

    if(!m_inventoryService->decreaseQuantity(product, &errorMessage)){
        emit messageRequested(errorMessage, QStringLiteral("red"));
        return;
    }

    m_productModel.decreaseQuantity(sourceIndex);

    emit historyChanged();


    emit messageRequested(
        product.name
            + QStringLiteral(" 수량을 ")
            + QString::number(product.quantity - 1)
            + QStringLiteral("개로 변경했습니다."),
        QStringLiteral("green")
        );

}

void InventoryViewModel::removeProduct(int proxyIndex)
{
    const int sourceIndex = toSourceIndex(proxyIndex);

    if(sourceIndex < 0){
        emit messageRequested(QStringLiteral("삭제할 상품을 찾을 수 없습니다."), QStringLiteral("red"));
        return;
    }

    const Product product = m_productModel.productAt(sourceIndex);

    QString errorMessage;

    if(!m_inventoryService->deleteProduct(product, &errorMessage)){
        emit messageRequested(QStringLiteral("상품 삭제에 실패했습니다:") + errorMessage, QStringLiteral("red"));
        return;
    }

    m_productModel.removeProduct(sourceIndex);

    emit historyChanged();

    emit messageRequested(product.name + QStringLiteral("상품을 삭제했습니다."), QStringLiteral("darkorange"));
}

void InventoryViewModel::resetFilters()
{
    setSearchText(QString());
    setStockFilter(QStringLiteral("all"));

    emit messageRequested(QStringLiteral("검색 조건을 초기화했습니다."), QStringLiteral("gray"));

}

int InventoryViewModel::toSourceIndex(int proxyIndex) const
{
    return m_filterModel.sourceIndex(proxyIndex);
}
