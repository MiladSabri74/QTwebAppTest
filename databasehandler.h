#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H


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
