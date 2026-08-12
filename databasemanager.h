#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>


class DatabaseManager
{
public:
    DatabaseManager();

    bool open();
    void close();

    bool isOpen() const;

    QSqlDatabase database() const;

    QString lastError() const;
    QString databasePath() const;


private:
    bool createTables();

    bool migrateDatabase();


    QSqlDatabase m_database;

    QString m_lastError;
    QString m_databasePath;
};


#endif // DATABASEMANAGER_H