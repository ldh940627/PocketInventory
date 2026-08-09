/****************************************************************************
** Meta object code from reading C++ file 'historyviewmodel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../historyviewmodel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'historyviewmodel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN16HistoryViewModelE_t {};
} // unnamed namespace

template <> constexpr inline auto HistoryViewModel::qt_create_metaobjectdata<qt_meta_tag_ZN16HistoryViewModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "HistoryViewModel",
        "countChanged",
        "",
        "actionFilterChanged",
        "searchTextChanged",
        "fromDateChanged",
        "toDateChanged",
        "datePresetChanged",
        "sortOrderChanged",
        "reload",
        "resetFilters",
        "setDateRange",
        "fromDateText",
        "toDateText",
        "sortNewestFirst",
        "sortOldestFirst",
        "showAllDates",
        "showToday",
        "showLast7Days",
        "showLast30Days",
        "history",
        "QAbstractItemModel*",
        "count",
        "actionFilter",
        "searchText",
        "fromDate",
        "toDate",
        "datePreset",
        "sortOrder"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'countChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'actionFilterChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'searchTextChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'fromDateChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'toDateChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'datePresetChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sortOrderChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'reload'
        QtMocHelpers::MethodData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'resetFilters'
        QtMocHelpers::MethodData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'setDateRange'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 12 }, { QMetaType::QString, 13 },
        }}),
        // Method 'sortNewestFirst'
        QtMocHelpers::MethodData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'sortOldestFirst'
        QtMocHelpers::MethodData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'showAllDates'
        QtMocHelpers::MethodData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'showToday'
        QtMocHelpers::MethodData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'showLast7Days'
        QtMocHelpers::MethodData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'showLast30Days'
        QtMocHelpers::MethodData<void()>(19, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'history'
        QtMocHelpers::PropertyData<QAbstractItemModel*>(20, 0x80000000 | 21, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'count'
        QtMocHelpers::PropertyData<int>(22, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'actionFilter'
        QtMocHelpers::PropertyData<QString>(23, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'searchText'
        QtMocHelpers::PropertyData<QString>(24, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'fromDate'
        QtMocHelpers::PropertyData<QDate>(25, QMetaType::QDate, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'toDate'
        QtMocHelpers::PropertyData<QDate>(26, QMetaType::QDate, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
        // property 'datePreset'
        QtMocHelpers::PropertyData<QString>(27, QMetaType::QString, QMC::DefaultPropertyFlags, 5),
        // property 'sortOrder'
        QtMocHelpers::PropertyData<QString>(28, QMetaType::QString, QMC::DefaultPropertyFlags, 6),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<HistoryViewModel, qt_meta_tag_ZN16HistoryViewModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject HistoryViewModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16HistoryViewModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16HistoryViewModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16HistoryViewModelE_t>.metaTypes,
    nullptr
} };

void HistoryViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<HistoryViewModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->countChanged(); break;
        case 1: _t->actionFilterChanged(); break;
        case 2: _t->searchTextChanged(); break;
        case 3: _t->fromDateChanged(); break;
        case 4: _t->toDateChanged(); break;
        case 5: _t->datePresetChanged(); break;
        case 6: _t->sortOrderChanged(); break;
        case 7: _t->reload(); break;
        case 8: _t->resetFilters(); break;
        case 9: _t->setDateRange((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 10: _t->sortNewestFirst(); break;
        case 11: _t->sortOldestFirst(); break;
        case 12: _t->showAllDates(); break;
        case 13: _t->showToday(); break;
        case 14: _t->showLast7Days(); break;
        case 15: _t->showLast30Days(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (HistoryViewModel::*)()>(_a, &HistoryViewModel::countChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (HistoryViewModel::*)()>(_a, &HistoryViewModel::actionFilterChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (HistoryViewModel::*)()>(_a, &HistoryViewModel::searchTextChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (HistoryViewModel::*)()>(_a, &HistoryViewModel::fromDateChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (HistoryViewModel::*)()>(_a, &HistoryViewModel::toDateChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (HistoryViewModel::*)()>(_a, &HistoryViewModel::datePresetChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (HistoryViewModel::*)()>(_a, &HistoryViewModel::sortOrderChanged, 6))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractItemModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QAbstractItemModel**>(_v) = _t->history(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->count(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->actionFilter(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->searchText(); break;
        case 4: *reinterpret_cast<QDate*>(_v) = _t->fromDate(); break;
        case 5: *reinterpret_cast<QDate*>(_v) = _t->toDate(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->datePreset(); break;
        case 7: *reinterpret_cast<QString*>(_v) = _t->sortOrder(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setActionFilter(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->setSearchText(*reinterpret_cast<QString*>(_v)); break;
        case 4: _t->setFromDate(*reinterpret_cast<QDate*>(_v)); break;
        case 5: _t->setToDate(*reinterpret_cast<QDate*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *HistoryViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HistoryViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16HistoryViewModelE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int HistoryViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void HistoryViewModel::countChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void HistoryViewModel::actionFilterChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void HistoryViewModel::searchTextChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void HistoryViewModel::fromDateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void HistoryViewModel::toDateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void HistoryViewModel::datePresetChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void HistoryViewModel::sortOrderChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
