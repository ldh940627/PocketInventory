#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QVariant>
#include <QQuickStyle>
#include <QDebug>

#include "DatabaseManager.h"
#include "historyviewmodel.h"
#include "inventoryviewmodel.h"
#include "productrepository.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle(QStringLiteral("Basic"));

    DatabaseManager databaseManager;

    if(!databaseManager.open()){
        qCritical() << "데이터베이스 연결 실패 :" << databaseManager.lastError();
        return -1;
    }

    ProductRepository productRepository(databaseManager.database());

    HistoryRepository historyRepository(databaseManager.database());

    InventoryService inventoryService(databaseManager.database(), &productRepository, &historyRepository);

    InventoryViewModel inventoryViewModel(&productRepository, &inventoryService);

    HistoryViewModel historyViewModel(&historyRepository);

    qDebug() << "데이터베이스 연결 성공: " << databaseManager.databasePath();

    QQmlApplicationEngine engine;

    engine.setInitialProperties({
        {
            QStringLiteral("inventoryViewModel"),
            QVariant::fromValue(&inventoryViewModel)
        },
        {
            QStringLiteral("historyViewModel"),
            QVariant::fromValue(&historyViewModel)
        }
    });

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    QObject::connect(
        &inventoryViewModel,
        &InventoryViewModel::historyChanged,
        &historyViewModel,
        &HistoryViewModel::reload);

    engine.loadFromModule("PocketInventory", "Main");

    const int exitCode = app.exec();

    databaseManager.close();

    return exitCode;

}
