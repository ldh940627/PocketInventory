#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>
#include <QtCore/qhash.h>
#include <QtCore/qstring.h>

namespace QmlCacheGeneratedCode {
namespace _qt_qml_PocketInventory_Main_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_PocketInventory_components_SummaryCard_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_PocketInventory_components_ProductDelegate_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_PocketInventory_components_SearchBar_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_PocketInventory_components_FilterBar_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_PocketInventory_components_ProductForm_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_PocketInventory_components_HistoryDelegate_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_PocketInventory_components_HistoryFilterBar_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/PocketInventory/Main.qml"), &QmlCacheGeneratedCode::_qt_qml_PocketInventory_Main_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/PocketInventory/components/SummaryCard.qml"), &QmlCacheGeneratedCode::_qt_qml_PocketInventory_components_SummaryCard_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/PocketInventory/components/ProductDelegate.qml"), &QmlCacheGeneratedCode::_qt_qml_PocketInventory_components_ProductDelegate_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/PocketInventory/components/SearchBar.qml"), &QmlCacheGeneratedCode::_qt_qml_PocketInventory_components_SearchBar_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/PocketInventory/components/FilterBar.qml"), &QmlCacheGeneratedCode::_qt_qml_PocketInventory_components_FilterBar_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/PocketInventory/components/ProductForm.qml"), &QmlCacheGeneratedCode::_qt_qml_PocketInventory_components_ProductForm_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/PocketInventory/components/HistoryDelegate.qml"), &QmlCacheGeneratedCode::_qt_qml_PocketInventory_components_HistoryDelegate_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/PocketInventory/components/HistoryFilterBar.qml"), &QmlCacheGeneratedCode::_qt_qml_PocketInventory_components_HistoryFilterBar_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.structVersion = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qmlcache_appPocketInventory)() {
    ::unitRegistry();
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qmlcache_appPocketInventory))
int QT_MANGLE_NAMESPACE(qCleanupResources_qmlcache_appPocketInventory)() {
    return 1;
}
