#include "DatabaseManager.h"

#include <QCoreApplication>
#include <QDir>
#include <QSqlError>
#include <QSqlQuery>


DatabaseManager::DatabaseManager()
{
    const QString dataDirectoryPath = QCoreApplication::applicationDirPath() + QStringLiteral("/data");

    QDir dataDirectory;

    if(!dataDirectory.exists(dataDirectoryPath)){
        dataDirectory.mkpath(dataDirectoryPath);
    }

    m_databasePath = dataDirectoryPath + QStringLiteral("/pocket_inventory.db");

}

bool DatabaseManager::open()
{
    if(m_database.isOpen()){
        return true;
    }

    if(QSqlDatabase::contains(QSqlDatabase::defaultConnection))
    {
        m_database = QSqlDatabase::database(QSqlDatabase::defaultConnection);
    }
    else
    {
        m_database = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
    }

    m_database.setDatabaseName(m_databasePath);

    if(!m_database.open()){
        m_lastError = m_database.lastError().text();

        return false;
    }

    if(!createTables()){
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

bool DatabaseManager::createTables()
{
    QSqlQuery query(m_database);
    const QString createProductsTable = QStringLiteral( "CREATE TABLE IF NOT EXISTS products ("
                                                       "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                       "name TEXT NOT NULL COLLATE NOCASE UNIQUE, "
                                                       "quantity INTEGER NOT NULL DEFAULT 0, "
                                                       "minimum_quantity INTEGER NOT NULL DEFAULT 0, "
                                                       "created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP, "
                                                       "updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP"
                                                       ")");

    if(!query.exec(createProductsTable)){
        m_lastError = query.lastError().text();

        return false;
    }

    return true;
}
