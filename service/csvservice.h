#ifndef CSVSERVICE_H
#define CSVSERVICE_H

#include <QString>
#include <QVector>

#include "productmodel.h"

struct CsvImportResult
{
    bool success = false;
    QVector<Product> products;
    QString errorMessage;
};

class csvservice
{
public:
    csvservice() = default;

    bool exportProduct(const QVector<Product> &products, const QString &filePath, QString *errorMessage = nullptr) const;
    CsvImportResult importProducts(const QString &filePath) const;

private:
    QString escapeCsvField(const QString &value) const;
    QStringList parseCsvLine(const QString &line, bool *success) const;

};


#endif // CSVSERVICE_H
