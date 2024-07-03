#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>


class Database {
public:

    // init Database
    static void initializeDatabase();

    // -------------------------- user table ----------------------------------
    // Authentication
    static bool validateUser(const QString& username, const QString& password);

    static bool checkExistanceUser(const QString& username);

    static bool addUser(const QString& username, const QString& password);

};
#endif // DATABASEHANDLER_H
