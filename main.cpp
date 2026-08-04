#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QVariant>

#include "productfilterproxymodel.h"
#include "productmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    ProductModel productModel;

    ProductFilterProxyModel productFilterModel;
    productFilterModel.setSourceModel(&productModel);

    engine.setInitialProperties({
        {
            QStringLiteral("productModel"),
            QVariant::fromValue(&productModel)
        },
        {
            QStringLiteral("productFilterModel"),
            QVariant::fromValue(&productFilterModel)
        }
    });

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("PocketInventory", "Main");

    return QGuiApplication::exec();
}
