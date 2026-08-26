#include "inventoryservice.h"
#include <QSqlError>
#include <QStringList>

InventoryService::InventoryService(const QSqlDatabase &database, ProductRepository *productRepository, HistoryRepository *historyRepository) : m_database(database), m_productRepository(productRepository), m_historyRepository(historyRepository)
{

}

bool InventoryService::updateProduct(const Product &product, const QString &name, int minimumQuantity, int unitPrice, QString *errorMessage)
{
    if(!m_productRepository || !m_historyRepository){
        if(errorMessage)
            *errorMessage = QStringLiteral("Repository가 연결되지 않았습니다.");
        return false;
    }

    const QString trimmedName = name.trimmed();

    if(trimmedName.isEmpty()){
        if(errorMessage)
            *errorMessage = QStringLiteral("상품명을 입력해주세요.");
        return false;
    }

    if(minimumQuantity < 0){
        if(errorMessage)
            *errorMessage = QStringLiteral("최소 재고는 0 이상이어야 합니다.");
        return false;
    }

    if(unitPrice < 0){
        if(errorMessage)
            *errorMessage = QStringLiteral("단가는 0 이상이어야 합니다.");
        return false;
    }

    QStringList changes;

    if(product.name != trimmedName)
        changes.append(QStringLiteral("상품명: %1 → %2").arg(product.name, trimmedName));

    if(product.minimumQuantity != minimumQuantity)
        changes.append(QStringLiteral("최소 재고: %1 → %2").arg(product.minimumQuantity).arg(minimumQuantity));

    if(product.unitPrice != unitPrice)
        changes.append(QStringLiteral("단가: %1 → %2").arg(product.unitPrice).arg(unitPrice));

    if(changes.isEmpty()){
        if(errorMessage)
            errorMessage->clear();
        return true;
    }

    const QString details = changes.join(QStringLiteral(" / "));

    if(!beginTransaction(errorMessage))
        return false;

    if(!m_productRepository->updateProductInfo(product.id, trimmedName, minimumQuantity, unitPrice, errorMessage)){
        rollbackTransaction();
        return false;
    }

    if(!m_historyRepository->insertHistory(product.id, trimmedName, product.quantity, product.quantity, QStringLiteral("EDIT"), details, errorMessage)){
        rollbackTransaction();
        return false;
    }

    if(!commitTransaction(errorMessage)){
        rollbackTransaction();
        return false;
    }

    if(errorMessage)
        errorMessage->clear();

    return true;

}

bool InventoryService::increaseQuantity(const Product &product, QString *errorMessage)
{
    if(!m_productRepository || !m_historyRepository){
        if(errorMessage)
            *errorMessage = QStringLiteral("Repository가 연결되지 않았습니다.");
                return false;
    }

    const int oldQuantity = product.quantity;
    const int newQuantity = oldQuantity + 1;

    if(!beginTransaction(errorMessage))
        return false;

    if(!m_productRepository->updateQuantity(product.id, newQuantity, errorMessage)){
        rollbackTransaction();
        return false;
    }

    if(!m_historyRepository->insertHistory(product.id, product.name,oldQuantity, newQuantity, QStringLiteral("INCREASE"),errorMessage)){
        rollbackTransaction();
        return false;
    }

    if(!commitTransaction(errorMessage)){
        rollbackTransaction();
        return false;
    }

    return true;

}

bool InventoryService::decreaseQuantity(const Product &product, QString *errorMessage)
{
    if(product.quantity <= 0){
        if(errorMessage){
            *errorMessage = QStringLiteral("재고는 0개보다 작을 수 없습니다.");
        }
        return false;
    }

    const int oldQuantity = product.quantity;
    const int newQuantity = oldQuantity - 1;

    if(!beginTransaction(errorMessage))
        return false;

    if(!m_productRepository->updateQuantity(product.id, newQuantity, errorMessage)){
        rollbackTransaction();
        return false;
    }

    if(!m_historyRepository->insertHistory(product.id, product.name,oldQuantity,newQuantity,QStringLiteral("DECREASE"), errorMessage)){
        rollbackTransaction();
        return false;
    }

    if(!commitTransaction(errorMessage)){
        rollbackTransaction();
        return false;
    }

    return true;

}

bool InventoryService::deleteProduct(const Product &product, QString *errorMessage)
{
    if(!beginTransaction(errorMessage))
        return false;

    if(!m_historyRepository->insertHistory(product.id, product.name, product.quantity,0, QStringLiteral("DELETE"),errorMessage)){
        rollbackTransaction();
        return false;
    }

    if(!m_productRepository->deleteProduct(product.id,errorMessage)){
        rollbackTransaction();
        return false;
    }

    if(!commitTransaction(errorMessage)){
        rollbackTransaction();
        return false;
    }

    return true;

}

bool InventoryService::adjustQuantity(const Product &product, int delta, const QString &action, QString *errorMessage)
{
    if(!m_productRepository || !m_historyRepository){
        if(errorMessage){
            *errorMessage = QStringLiteral("Repository가 연결되지 않았습니다.");
        }
        return false;
    }

    const int oldQuantity = product.quantity;
    const int newQuantity = oldQuantity + delta;

    if(newQuantity < 0){
        if(errorMessage){
            *errorMessage = QStringLiteral("재고는 0개보다 작을 수 없습니다.");
        }
        return false;
    }

    if(!beginTransaction(errorMessage))
        return false;

    if(!m_productRepository->updateQuantity(product.id, newQuantity, errorMessage)){
        rollbackTransaction();
        return false;
    }

    if(!m_historyRepository->insertHistory(product.id, product.name, oldQuantity, newQuantity, action, errorMessage)){
        rollbackTransaction();
        return false;
    }

    if(!commitTransaction(errorMessage)){
        rollbackTransaction();
        return false;
    }

    return true;
}

int InventoryService::addProduct(const QString &name, int quantity, int minimumQuantity, int unitPrice, const QString &category, QString *errorMessage)
{

    if(!m_productRepository || !m_historyRepository){
        if(errorMessage){
            *errorMessage =
                QStringLiteral("Repository가 연결되지 않았습니다.");
        }

        return -1;
    }

    if(!beginTransaction(errorMessage)){
        return -1;
    }

    qDebug() << "[ADD] Product INSERT 시작";

    const int productId =
        m_productRepository->insertProduct(
            name,
            quantity,
            minimumQuantity,
            unitPrice, category,
            errorMessage
            );

    if(productId < 0){
        qDebug()
        << "[ADD] Product INSERT 실패:"
        << (errorMessage ? *errorMessage : QString());

        rollbackTransaction();
        return -1;
    }

    qDebug()
        << "[ADD] Product INSERT 성공:"
        << productId;


    qDebug() << "[ADD] History INSERT 시작";

    if(!m_historyRepository->insertHistory(
            productId,
            name,
            0,
            quantity,
            QStringLiteral("CREATE"),
            errorMessage
            ))
    {
        qDebug()
        << "[ADD] History INSERT 실패:"
        << (errorMessage ? *errorMessage : QString());

        rollbackTransaction();
        return -1;
    }

    qDebug()
        << "[ADD] History INSERT 성공";


    if(!commitTransaction(errorMessage)){
        qDebug()
        << "[ADD] Commit 실패:"
        << (errorMessage ? *errorMessage : QString());

        rollbackTransaction();
        return -1;
    }

    qDebug() << "[ADD] Commit 성공";

    return productId;

}

bool InventoryService::beginTransaction(QString *errorMessage)
{
    if(!m_database.transaction()){
        if(errorMessage)
            *errorMessage = m_database.lastError().text();

        return false;
    }

    return true;

}

bool InventoryService::commitTransaction(QString *errorMessage)
{
    if(!m_database.commit()){
        if(errorMessage)
            *errorMessage = m_database.lastError().text();
        return false;
    }

    return true;

}

void InventoryService::rollbackTransaction()
{
    m_database.rollback();
}
