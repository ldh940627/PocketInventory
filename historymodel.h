#ifndef HISTORYMODEL_H
#define HISTORYMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "historyrecord.h"

class HistoryModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY countChanged)


public:

    enum HistoryRole
    {
        HistoryIdRole = Qt::UserRole + 1,
        ProductIdRole, ProductNameRole, OldQuantityRole, NewQuantityRole,
        ActionRole, CreatedAtRole
    };

    explicit HistoryModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int count() const;
    void setHistory(const QList<HistoryRecord> &history);

signals:
    void countChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<HistoryRecord> m_history;
};

#endif // HISTORYMODEL_H
