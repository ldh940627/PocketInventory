#include "csvservice.h"

#include <QFile>
#include <QTextStream>
#include <QStringConverter>


bool csvservice::exportProduct(const QVector<Product> &products, const QString &filePath, QString *errorMessage) const
{
    QFile file(filePath);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        if(errorMessage){
            *errorMessage = QStringLiteral("CSV 파일을 저장할 수 없습니다: %1").arg(file.errorString());
        }

        return false;
    }

    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    stream.setGenerateByteOrderMark(true);

    stream << QStringLiteral("상품명,카테고리,현재재고,최소재고,단가,재고금액\n");

    for(const Product &product : products){
        const qint64 inventoryValue = static_cast<qint64>(product.quantity) * product.unitPrice;

        stream << escapeCsvField(product.name) << ","
               << escapeCsvField(product.category.isEmpty() ? QStringLiteral("미분류") : product.category) << ","
               << product.quantity << ","
               << product.minimumQuantity << ","
               << product.unitPrice << ","
               << inventoryValue << "\n";
    }

    return true;

}

CsvImportResult csvservice::importProducts(const QString &filePath) const
{
    CsvImportResult result;

    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        result.errorMessage = QStringLiteral("CSV 파일을 열 수 없습니다: %1").arg(file.errorString());
        return result;
    }

    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);

    if(stream.atEnd()){
        result.errorMessage = QStringLiteral("CSV 파일이 비어 있습니다.");
        return result;
    }

    const QString headerLine = stream.readLine();

    bool headerParseSuccess = false;
    const QStringList headers = parseCsvLine(headerLine, &headerParseSuccess);

    if(!headerParseSuccess){
        result.errorMessage = QStringLiteral("CSV 헤더 형식이 올바르지 않습니다.");
        return result;
    }

    const QStringList expectedHeaders = {
        QStringLiteral("상품명"),
        QStringLiteral("카테고리"),
        QStringLiteral("현재재고"),
        QStringLiteral("최소재고"),
        QStringLiteral("단가"),
        QStringLiteral("재고금액")
    };

    if(headers != expectedHeaders){
        result.errorMessage = QStringLiteral("CSV 헤더 형식이 PocketInventory 형식과 일치하지 않습니다.");
        return result;
    }

    QSet<QString> productNames;
    int lineNumber = 1;

    while(!stream.atEnd()){
        const QString line = stream.readLine();
        ++lineNumber;

        if(line.trimmed().isEmpty()){
            continue;
        }

        bool parseSuccess = false;
        const QStringList fields = parseCsvLine(line, &parseSuccess);

        if(!parseSuccess){
            result.errorMessage = QStringLiteral("%1행의 CSV 형식이 올바르지 않습니다.").arg(lineNumber);
            return result;
        }

        if(fields.size() != 6){
            result.errorMessage = QStringLiteral("%1행의 열 개수가 올바르지 않습니다.").arg(lineNumber);
            return result;
        }

        const QString name = fields[0].trimmed();
        QString category = fields[1].trimmed();

        if(name.isEmpty()){
            result.errorMessage = QStringLiteral("%1행의 상품명이 비어 있습니다.").arg(lineNumber);
            return result;
        }

        bool quantityOk = false;
        bool minimumQuantityOk = false;
        bool unitPriceOk = false;

        const int quantity = fields[2].trimmed().toInt(&quantityOk);
        const int minimumQuantity = fields[3].trimmed().toInt(&minimumQuantityOk);
        const int unitPrice = fields[4].trimmed().toInt(&unitPriceOk);

        if(!quantityOk){
            result.errorMessage = QStringLiteral("%1행의 현재재고가 올바른 숫자가 아닙니다.").arg(lineNumber);
            return result;
        }

        if(!minimumQuantityOk){
            result.errorMessage = QStringLiteral("%1행의 최소재고가 올바른 숫자가 아닙니다.").arg(lineNumber);
            return result;
        }

        if(!unitPriceOk){
            result.errorMessage = QStringLiteral("%1행의 단가가 올바른 숫자가 아닙니다.").arg(lineNumber);
            return result;
        }

        if(quantity < 0 || minimumQuantity < 0 || unitPrice < 0){
            result.errorMessage = QStringLiteral("%1행에는 음수를 사용할 수 없습니다.").arg(lineNumber);
            return result;
        }

        const QString normalizedName = name.toCaseFolded();

        if(productNames.contains(normalizedName)){
            result.errorMessage = QStringLiteral("%1행의 상품명 '%2'이 CSV 파일 안에서 중복되었습니다.").arg(lineNumber).arg(name);
            return result;
        }

        productNames.insert(normalizedName);

        if(category == QStringLiteral("미분류")){
            category.clear();
        }

        Product product;
        product.name = name;
        product.quantity = quantity;
        product.minimumQuantity = minimumQuantity;
        product.unitPrice = unitPrice;
        product.category = category;

        result.products.append(product);
    }

    if(result.products.isEmpty()){
        result.errorMessage = QStringLiteral("가져올 상품이 없습니다.");
        return result;
    }

    result.success = true;
    return result;
}

QString csvservice::escapeCsvField(const QString &value) const
{
    QString escaped = value;
    escaped.replace("\"", "\"\"");

    if(escaped.contains(',') || escaped.contains('"') || escaped.contains('\n') || escaped.contains('\r')){
        escaped = "\"" + escaped + "\"";
    }

    return escaped;
}

QStringList csvservice::parseCsvLine(const QString &line, bool *success) const
{
    QStringList fields;
    QString currentField;
    bool insideQuotes = false;

    for(int i = 0; i < line.size(); ++i){
        const QChar ch = line[i];

        if(ch == '"'){
            if(insideQuotes && i + 1 < line.size() && line[i + 1] == '"'){
                currentField += '"';
                ++i;
            }
            else{
                insideQuotes = !insideQuotes;
            }
        }
        else if(ch == ',' && !insideQuotes){
            fields.append(currentField);
            currentField.clear();
        }
        else{
            currentField += ch;
        }
    }

    if(insideQuotes){
        if(success){
            *success = false;
        }
        return {};
    }

    fields.append(currentField);

    if(success){
        *success = true;
    }

    return fields;

}
