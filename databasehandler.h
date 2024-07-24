#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H


class Database {
public:

    // init Database
    static void initializeDatabase();

    // -------------------------- user table ----------------------------------
    // Authentication
    static bool validateUser(const QString& username, const QString& password,int* userAccessLevel);

    static bool checkExistanceUser(const QString& username,int tokenAccessLevel);

    static bool addUser(const QString& username, const QString& password);

};
#endif // DATABASEHANDLER_H
