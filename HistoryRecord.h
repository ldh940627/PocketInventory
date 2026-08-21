#ifndef HISTORYRECORD_H
#define HISTORYRECORD_H

#include <QString>

struct HistoryRecord
{
    int id = -1;
    int productId = -1;

    QString productName;

    int oldQuantity = 0;
    int newQuantity = 0;

    QString action;
    QString details;
    QString createdAt;

};

#endif // HISTORYRECORD_H
