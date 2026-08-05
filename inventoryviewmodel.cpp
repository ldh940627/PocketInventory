#include "inventoryviewmodel.h"
#include <QDebug>


InventoryViewModel::InventoryViewModel(ProductRepository *productrepository, HistoryRepository *historyrepository, QObject *parent)
    : QObject(parent), m_productRepository(productrepository), m_historyRepository(historyrepository)
{
    m_filterModel.setSourceModel(&m_productModel);

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

    QString databaseError;

    const int productId = m_productRepository->insertProduct(productName, quantity, minimumQuantity, &databaseError);

    if(productId < 0){
        emit messageRequested(QStringLiteral("상품을 저장하지 못했습니다: ") + databaseError, QStringLiteral("red"));
        return false;
    }

    if(!m_productModel.addProduct(productId, productName, quantity, minimumQuantity)){
        emit messageRequested(QStringLiteral("상품은 DB에 저장됐지만 " "화면 모델 갱신에 실패했습니다."), QStringLiteral("red"));
        return false;
    }

    emit messageRequested(productName + QStringLiteral(" 상품이 등록되었습니다."), QStringLiteral("green"));

    if(m_historyRepository){
        QString historyError;

        if(!m_historyRepository->insertHistory(productId, productName, 0, quantity, QStringLiteral("CREATE"), &historyError)){
            qWarning() << "상품 등록 이력 저장 실패:" << historyError;
        }
    }

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
    const int oldQuantity = product.quantity;
    const int newQuantity = oldQuantity +1;

    QString errorMessage;

    if(!m_productRepository->updateQuantity(product.id, newQuantity, &errorMessage))
    {
        emit messageRequested(
            QStringLiteral("수량을 저장하지 못했습니다: ") + errorMessage, QStringLiteral("red"));
        return;
    }

    if(m_historyRepository && !m_historyRepository->insertHistory(product.id, product.name,
        oldQuantity, newQuantity, QStringLiteral("INCREASE"),&errorMessage))
    {
        emit messageRequested(QStringLiteral("재고 이력 저장에 실패했습니다.") + errorMessage, QStringLiteral("red"));
        return;
    }

    if(!m_productModel.increaseQuantity(sourceIndex)){
        emit messageRequested(QStringLiteral("수량 변경에 실패했습니다."), QStringLiteral("red"));
        return;
    }

    emit messageRequested(
        product.name
            + QStringLiteral(" 수량을 ")
            + QString::number(newQuantity)
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

    if (product.quantity <= 0) {
        emit messageRequested(QStringLiteral("재고는 0개보다 작을 수 없습니다."), QStringLiteral("red"));

        return;
    }


    const int oldQuantity = product.quantity;
    const int newQuantity = oldQuantity -1;

    QString error;

    if(!m_productRepository->updateQuantity(product.id, newQuantity, &error))
    {
        emit messageRequested("DB 저장 실패 : " + error, "red");

        return;
    }

    if(m_historyRepository && !m_historyRepository->insertHistory(product.id, product.name, oldQuantity,
        newQuantity, QStringLiteral("DECREASE"), &error)){
        emit messageRequested(QStringLiteral("재고 이력 저장에 실패했습니다: ") + error, QStringLiteral("red"));
        return;
    }

    if(!m_productModel.decreaseQuantity(sourceIndex)){
        emit messageRequested(QStringLiteral("화면 수량 갱신에 실패했습니다."), QStringLiteral("red"));
        return;
    }

    emit messageRequested(
        product.name
            + QStringLiteral(" 수량을 ")
            + QString::number(newQuantity)
            + QStringLiteral(
                "개로 변경했습니다."
                ),
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

    QString error;

    if(!m_productRepository->deleteProduct(product.id, &error))
    {
        emit messageRequested("DB 삭제 실패", "red");
        return;
    }

    if(m_historyRepository && !m_historyRepository->insertHistory(product.id, product.name, product.quantity, 0,
                                                                   QStringLiteral("DELETE"), &error)){
        emit messageRequested(QStringLiteral("삭제 이력 저장에 실패했습니다:") + error, QStringLiteral("red"));
        return;
    }


    if(!m_productModel.removeProduct(sourceIndex)){
        emit messageRequested(QStringLiteral("상품 삭제에 실패했습니다"), QStringLiteral("red"));
        return;
    }

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
