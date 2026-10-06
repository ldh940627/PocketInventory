/****************************************************************************
** Meta object code from reading C++ file 'inventoryviewmodel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../inventoryviewmodel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inventoryviewmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN18InventoryViewModelE_t {};
} // unnamed namespace

template <> constexpr inline auto InventoryViewModel::qt_create_metaobjectdata<qt_meta_tag_ZN18InventoryViewModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "InventoryViewModel",
        "stockSummaryChanged",
        "",
        "filteredCountChanged",
        "searchTextChanged",
        "stockFilterChanged",
        "messageRequested",
        "message",
        "colorName",
        "historyChanged",
        "categoriesChanged",
        "categoryFilterChanged",
        "categorySummaryChanged",
        "addProduct",
        "productNameText",
        "productQuantityText",
        "minimumQuantityText",
        "unitPriceText",
        "categoryText",
        "updateProduct",
        "proxyIndex",
        "receiveStock",
        "quantityText",
        "releaseStock",
        "increaseQuantity",
        "decreaseQuantity",
        "removeProduct",
        "resetFilters",
        "exportProducts",
        "QUrl",
        "fileUrl",
        "importProducts",
        "products",
        "QAbstractItemModel*",
        "lowStockProducts",
        "totalCount",
        "normalStockCount",
        "lowStockCount",
        "totalInventoryValue",
        "filteredCount",
        "searchText",
        "stockFilter",
        "categories",
        "categoryFilter",
        "categorySummary",
        "QVariantList"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'stockSummaryChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'filteredCountChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'searchTextChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'stockFilterChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'messageRequested'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 }, { QMetaType::QString, 8 },
        }}),
        // Signal 'historyChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'categoriesChanged'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'categoryFilterChanged'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'categorySummaryChanged'
        QtMocHelpers::SignalData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'addProduct'
        QtMocHelpers::MethodData<bool(const QString &, const QString &, const QString &, const QString &, const QString &)>(13, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 14 }, { QMetaType::QString, 15 }, { QMetaType::QString, 16 }, { QMetaType::QString, 17 },
            { QMetaType::QString, 18 },
        }}),
        // Method 'updateProduct'
        QtMocHelpers::MethodData<bool(int, const QString &, const QString &, const QString &, const QString &)>(19, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 20 }, { QMetaType::QString, 14 }, { QMetaType::QString, 16 }, { QMetaType::QString, 17 },
            { QMetaType::QString, 18 },
        }}),
        // Method 'receiveStock'
        QtMocHelpers::MethodData<bool(int, const QString &)>(21, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 20 }, { QMetaType::QString, 22 },
        }}),
        // Method 'releaseStock'
        QtMocHelpers::MethodData<bool(int, const QString &)>(23, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 20 }, { QMetaType::QString, 22 },
        }}),
        // Method 'increaseQuantity'
        QtMocHelpers::MethodData<void(int)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 20 },
        }}),
        // Method 'decreaseQuantity'
        QtMocHelpers::MethodData<void(int)>(25, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 20 },
        }}),
        // Method 'removeProduct'
        QtMocHelpers::MethodData<void(int)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 20 },
        }}),
        // Method 'resetFilters'
        QtMocHelpers::MethodData<void()>(27, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'exportProducts'
        QtMocHelpers::MethodData<bool(const QUrl &)>(28, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { 0x80000000 | 29, 30 },
        }}),
        // Method 'importProducts'
        QtMocHelpers::MethodData<bool(const QUrl &)>(31, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { 0x80000000 | 29, 30 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'products'
        QtMocHelpers::PropertyData<QAbstractItemModel*>(32, 0x80000000 | 33, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'lowStockProducts'
        QtMocHelpers::PropertyData<QAbstractItemModel*>(34, 0x80000000 | 33, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'totalCount'
        QtMocHelpers::PropertyData<int>(35, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'normalStockCount'
        QtMocHelpers::PropertyData<int>(36, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'lowStockCount'
        QtMocHelpers::PropertyData<int>(37, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'totalInventoryValue'
        QtMocHelpers::PropertyData<qint64>(38, QMetaType::LongLong, QMC::DefaultPropertyFlags, 0),
        // property 'filteredCount'
        QtMocHelpers::PropertyData<int>(39, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'searchText'
        QtMocHelpers::PropertyData<QString>(40, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'stockFilter'
        QtMocHelpers::PropertyData<QString>(41, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'categories'
        QtMocHelpers::PropertyData<QStringList>(42, QMetaType::QStringList, QMC::DefaultPropertyFlags, 6),
        // property 'categoryFilter'
        QtMocHelpers::PropertyData<QString>(43, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 7),
        // property 'categorySummary'
        QtMocHelpers::PropertyData<QVariantList>(44, 0x80000000 | 45, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 8),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<InventoryViewModel, qt_meta_tag_ZN18InventoryViewModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject InventoryViewModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18InventoryViewModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18InventoryViewModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN18InventoryViewModelE_t>.metaTypes,
    nullptr
} };

void InventoryViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<InventoryViewModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->stockSummaryChanged(); break;
        case 1: _t->filteredCountChanged(); break;
        case 2: _t->searchTextChanged(); break;
        case 3: _t->stockFilterChanged(); break;
        case 4: _t->messageRequested((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->historyChanged(); break;
        case 6: _t->categoriesChanged(); break;
        case 7: _t->categoryFilterChanged(); break;
        case 8: _t->categorySummaryChanged(); break;
        case 9: { bool _r = _t->addProduct((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[5])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->updateProduct((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[5])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 11: { bool _r = _t->receiveStock((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->releaseStock((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->increaseQuantity((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->decreaseQuantity((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->removeProduct((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 16: _t->resetFilters(); break;
        case 17: { bool _r = _t->exportProducts((*reinterpret_cast<std::add_pointer_t<QUrl>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 18: { bool _r = _t->importProducts((*reinterpret_cast<std::add_pointer_t<QUrl>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (InventoryViewModel::*)()>(_a, &InventoryViewModel::stockSummaryChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (InventoryViewModel::*)()>(_a, &InventoryViewModel::filteredCountChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (InventoryViewModel::*)()>(_a, &InventoryViewModel::searchTextChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (InventoryViewModel::*)()>(_a, &InventoryViewModel::stockFilterChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (InventoryViewModel::*)(const QString & , const QString & )>(_a, &InventoryViewModel::messageRequested, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (InventoryViewModel::*)()>(_a, &InventoryViewModel::historyChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (InventoryViewModel::*)()>(_a, &InventoryViewModel::categoriesChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (InventoryViewModel::*)()>(_a, &InventoryViewModel::categoryFilterChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (InventoryViewModel::*)()>(_a, &InventoryViewModel::categorySummaryChanged, 8))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractItemModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QAbstractItemModel**>(_v) = _t->products(); break;
        case 1: *reinterpret_cast<QAbstractItemModel**>(_v) = _t->lowStockProducts(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->totalCount(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->normalStockCount(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->lowStockCount(); break;
        case 5: *reinterpret_cast<qint64*>(_v) = _t->totalInventoryValue(); break;
        case 6: *reinterpret_cast<int*>(_v) = _t->filteredCount(); break;
        case 7: *reinterpret_cast<QString*>(_v) = _t->searchText(); break;
        case 8: *reinterpret_cast<QString*>(_v) = _t->stockFilter(); break;
        case 9: *reinterpret_cast<QStringList*>(_v) = _t->categories(); break;
        case 10: *reinterpret_cast<QString*>(_v) = _t->categoryFilter(); break;
        case 11: *reinterpret_cast<QVariantList*>(_v) = _t->categorySummary(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 7: _t->setSearchText(*reinterpret_cast<QString*>(_v)); break;
        case 8: _t->setStockFilter(*reinterpret_cast<QString*>(_v)); break;
        case 10: _t->setCategoryFilter(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *InventoryViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InventoryViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18InventoryViewModelE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int InventoryViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void InventoryViewModel::stockSummaryChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void InventoryViewModel::filteredCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void InventoryViewModel::searchTextChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void InventoryViewModel::stockFilterChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void InventoryViewModel::messageRequested(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}

// SIGNAL 5
void InventoryViewModel::historyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void InventoryViewModel::categoriesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void InventoryViewModel::categoryFilterChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void InventoryViewModel::categorySummaryChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
