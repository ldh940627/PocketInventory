#include "DatabaseManager.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QSqlError>
#include <QSqlQuery>


DatabaseManager::DatabaseManager()
{
    const QString dataDirectoryPath =
        QCoreApplication::applicationDirPath()
        + QStringLiteral("/data");

    QDir dataDirectory;

    if(!dataDirectory.exists(dataDirectoryPath)){
        dataDirectory.mkpath(dataDirectoryPath);
    }

    m_databasePath =
        dataDirectoryPath
        + QStringLiteral("/pocket_inventory.db");
}


bool DatabaseManager::open()
{
    if(m_database.isOpen()){
        return true;
    }

    if(QSqlDatabase::contains(
            QSqlDatabase::defaultConnection
            ))
    {
        m_database =
            QSqlDatabase::database(
                QSqlDatabase::defaultConnection
                );
    }
    else
    {
        m_database =
            QSqlDatabase::addDatabase(
                QStringLiteral("QSQLITE")
                );
    }


    m_database.setDatabaseName(
        m_databasePath
        );


    if(!m_database.open()){
        m_lastError =
            m_database.lastError().text();

        return false;
    }


    // ============================================================
    // 테이블 생성
    // ============================================================

    if(!createTables()){
        m_database.close();
        return false;
    }


    // ============================================================
    // 기존 DB Migration
    // ============================================================

    if(!migrateDatabase()){
        m_database.close();
        return false;
    }


    m_lastError.clear();

    return true;
}


void DatabaseManager::close()
{
    if(m_database.isOpen()){
        m_database.close();
    }
}


bool DatabaseManager::isOpen() const
{
    return m_database.isOpen();
}


QSqlDatabase DatabaseManager::database() const
{
    return m_database;
}


QString DatabaseManager::lastError() const
{
    return m_lastError;
}


QString DatabaseManager::databasePath() const
{
    return m_databasePath;
}


// ================================================================
// Create Tables
// ================================================================

bool DatabaseManager::createTables()
{
    QSqlQuery query(m_database);


    // ============================================================
    // Products
    // 신규 DB는 처음부터 unit_price를 포함
    // ============================================================

    const QString createProductsTable =
        QStringLiteral(
            "CREATE TABLE IF NOT EXISTS products ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name TEXT NOT NULL COLLATE NOCASE UNIQUE, "
            "quantity INTEGER NOT NULL DEFAULT 0, "
            "minimum_quantity INTEGER NOT NULL DEFAULT 0, "
            "unit_price INTEGER NOT NULL DEFAULT 0, "
            "category TEXT NOT NULL DEFAULT '', "
            "created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP, "
            "updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP"
            ")"
            );


    if(!query.exec(createProductsTable)){
        m_lastError =
            QStringLiteral(
                "products 테이블 생성 실패: "
                )
            + query.lastError().text();

        return false;
    }


    // ============================================================
    // History
    // ============================================================

    const QString createHistoryTable =
        QStringLiteral(
        "CREATE TABLE IF NOT EXISTS history ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "product_id INTEGER NOT NULL, "
        "product_name TEXT NOT NULL, "
        "old_quantity INTEGER NOT NULL, "
        "new_quantity INTEGER NOT NULL, "
        "action TEXT NOT NULL, "
        "details TEXT NOT NULL DEFAULT '', "
        "created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP"
        ")");


    if(!query.exec(createHistoryTable)){
        m_lastError =
            QStringLiteral(
                "history 테이블 생성 실패: "
                )
            + query.lastError().text();

        return false;
    }


    return true;
}


// ================================================================
// Database Migration
// ================================================================

bool DatabaseManager::migrateDatabase()
{
    QSqlQuery query(m_database);

    // ============================================================
    // 현재 products 컬럼 확인
    // ============================================================

    if(!query.exec(QStringLiteral("PRAGMA table_info(products)")))
    {
        m_lastError = QStringLiteral("products 테이블 구조 확인 실패: ") + query.lastError().text();

        return false;
    }

    bool hasUnitPrice = false;
    bool hasCategory = false;

    qDebug() << "===== products columns =====";

    while(query.next()){

        const QString columnName = query.value(1).toString();

        qDebug() << columnName;

        if(columnName.compare(QStringLiteral("unit_price"), Qt::CaseInsensitive) == 0)
        {
            hasUnitPrice = true;
        }

        if(columnName.compare(QStringLiteral("category"), Qt::CaseInsensitive) == 0){
            hasCategory = true;
        }
    }

    // ============================================================
    // 기존 DB에 unit_price가 없다면 추가
    // ============================================================

    if(!hasUnitPrice){

        qDebug() << "[Migration]" << "unit_price 컬럼이 없습니다." << "Migration을 시작합니다.";

        QSqlQuery alterQuery(m_database);

        const QString alterSql = QStringLiteral(
                "ALTER TABLE products "
                "ADD COLUMN unit_price "
                "INTEGER NOT NULL DEFAULT 0"
                );

        if(!alterQuery.exec(alterSql)){

            m_lastError = QStringLiteral("unit_price 컬럼 추가 실패: ") + alterQuery.lastError().text();
            qWarning() << "[Migration 실패]" << m_lastError;
            return false;
        }

        qDebug() << "[Migration 성공]"  << "products.unit_price 컬럼 추가 완료";
    }
    else
    {
        qDebug()  << "[Migration]" << "unit_price 컬럼이 이미 존재합니다.";
    }

    if(!hasCategory){
        qDebug() << "[Migration] category 컬럼이 없습니다. Migration을 시작합니다.";

        QSqlQuery alterCategoryQuery(m_database);
        const QString alterSql = QStringLiteral("ALTER TABLE products ADD COLUMN category TEXT NOT NULL DEFAULT ''");

        if(!alterCategoryQuery.exec(alterSql)){
            m_lastError = QStringLiteral("category 컬럼 추가 실패: ") + alterCategoryQuery.lastError().text();
            qWarning() << "[Migration 실패]" << m_lastError;
            return false;
        }

        qDebug() << "[Migration 성공] products.category 컬럼 추가 완료";
    }
    else{
        qDebug() << "[Migration] category 컬럼이 이미 존재합니다.";
    }

    // ============================================================
    // History details 컬럼 Migration
    // ============================================================

    QSqlQuery historyInfoQuery(m_database);

    if(!historyInfoQuery.exec(QStringLiteral("PRAGMA table_info(history)"))){
        m_lastError = QStringLiteral("history 테이블 구조 확인 실패: ") + historyInfoQuery.lastError().text();
        return false;
    }

    bool hasDetails = false;

    while(historyInfoQuery.next()){
        const QString columnName = historyInfoQuery.value(1).toString();

        if(columnName.compare(QStringLiteral("details"), Qt::CaseInsensitive) == 0){
            hasDetails = true;
            break;
        }
    }

    if(!hasDetails){
        QSqlQuery alterHistoryQuery(m_database);

        const QString alterSql = QStringLiteral("ALTER TABLE history ADD COLUMN details TEXT NOT NULL DEFAULT ''");

        if(!alterHistoryQuery.exec(alterSql)){
            m_lastError = QStringLiteral("history.details 컬럼 추가 실패: ") + alterHistoryQuery.lastError().text();
            qWarning() << "[Migration 실패]" << m_lastError;
            qWarning() << "[실행 SQL]" << alterSql;
            return false;
        }

        qDebug() << "[Migration 성공] history.details 컬럼 추가 완료";
    }
    else{
        qDebug() << "[Migration] history.details 컬럼이 이미 존재합니다.";
    }

    return true;
}