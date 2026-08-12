#include "historymodel.h"


HistoryModel::HistoryModel(QObject *parent) : QAbstractListModel(parent)
{

}

int HistoryModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return m_history.count();
}

QVariant HistoryModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return {};

    if(index.row() < 0 || index.row() >= m_history.count()){
        return {};
    }

    const HistoryRecord &record = m_history.at(index.row());

    switch (role) {
    case HistoryIdRole:
        return record.id;
    case ProductIdRole:
        return record.productId;
    case ProductNameRole:
        return record.productName;
    case OldQuantityRole:
        return record.oldQuantity;
    case NewQuantityRole:
        return record.newQuantity;
    case ActionRole:
        return record.action;
    case CreatedAtRole:
        return record.createdAt;

    default:
        return {};
    }
}

int HistoryModel::count() const
{
    return m_history.count();
}

void HistoryModel::setHistory(const QList<HistoryRecord> &history)
{
    beginResetModel();

    m_history = history;

    endResetModel();

    emit countChanged();
}

QHash<int, QByteArray> HistoryModel::roleNames() const
{
    return{
        {HistoryIdRole, "historyId"},
        {ProductIdRole, "productId"},
        {ProductNameRole, "productName"},
        {OldQuantityRole, "oldQuantity"},
        {NewQuantityRole, "newQuantity"},
        {ActionRole, "action"},
        {CreatedAtRole, "createdAt"}
    };
}
