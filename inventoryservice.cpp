#include "inventoryservice.h"
#include <QSqlError>

InventoryService::InventoryService(const QSqlDatabase &database, ProductRepository *productRepository, HistoryRepository *historyRepository) : m_database(database), m_productRepository(productRepository), m_historyRepository(historyRepository)
{

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

int InventoryService::addProduct(const QString &name, int quantity, int minimumQuantity, QString *errorMessage)
{

    if(!m_productRepository || !m_historyRepository){
        if(errorMessage){
            *errorMessage = QStringLiteral("Repository가 연결되지 않았습니다.");
        }
        return -1;
    }

    if(!beginTransaction(errorMessage)){
        // qDebug() << "[ADD] Transaction 시작 실패:"
        //          << (errorMessage ? *errorMessage : QString());
        return -1;
    }


    const int productId = m_productRepository->insertProduct(name, quantity, minimumQuantity, errorMessage);

    if(productId < 0){
        // qDebug() << "[ADD] Product INSERT 실패:"
        //          << (errorMessage ? *errorMessage : QString());
        rollbackTransaction();
        return -1;
    }

    // qDebug() << "[ADD] Product INSERT 성공:"
    //          << productId;

    if(!m_historyRepository->insertHistory(productId, name, 0, quantity, QStringLiteral("CREATE"), errorMessage)){
        // qDebug() << "[ADD] History INSERT 실패:"
        //          << (errorMessage ? *errorMessage : QString());
        rollbackTransaction();
        return -1;
    }

     // qDebug() << "[ADD] History INSERT 성공";

    if(!commitTransaction(errorMessage)){
        // qDebug() << "[ADD] Commit 실패:"
        //           << (errorMessage ? *errorMessage : QString());
        rollbackTransaction();
        return -1;
    }

    // qDebug()
    //     << "[ADD] History INSERT 성공";

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
