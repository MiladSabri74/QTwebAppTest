#include "databasehandler.h"
#include <QString>

void Database::initializeDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("novintest");
    db.setUserName("postgres");
    db.setPassword("123456");

    if (!db.open()) {
        qFatal("Failed to connect to database: %s", qPrintable(db.lastError().text()));
    } else {
        qDebug() << "Database connection established.";
    }
}



bool Database::validateUser(const QString& username, const QString& password,int* userAccessLevel) {
    QSqlQuery query;
    QString accessLevel = "";
    query.prepare("SELECT access_level,password FROM users WHERE username = :username");
    query.bindValue(":username", username);


    if (!query.exec()) {
        qDebug() << "Database query failed:" << query.lastError();
        return false;
    }

    if (query.next()) {
        accessLevel = query.value(0).toString();
        qDebug() << "ACCESS-LEVEL-DB: " << accessLevel;
        *userAccessLevel = accessLevel.toInt();
        QString storedPassword = query.value(1).toString();
        return storedPassword == password;
    }

    return false;
}

bool Database::checkExistanceUser(const QString& username,int tokenAccessLevel) {
    // define variables
    QSqlQuery query;
    int databaseAccessLevel = 0;
    bool isValid = false;

    // create query
    query.prepare("SELECT access_level FROM users WHERE username = :username");
    query.bindValue(":username", username);

    // execute query
    if (!query.exec()) {
        qDebug() << "Database query failed:" << query.lastError();
        return false;
    }

    // extract parameters from databases
    if (query.next()) {
        databaseAccessLevel = query.value(0).toString().toInt(&isValid,10);
        // check validation of access-level
        if(isValid && databaseAccessLevel <= MAX_ACCESS_LEVEL && tokenAccessLevel==databaseAccessLevel) {
            qDebug() << "ACCESS-LEVEL-DB: " << databaseAccessLevel;
            return true;
        }
    }
    return false;
}

bool Database::addUser(const QString& username, const QString& password) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password,access_level) VALUES (:username, :password,:access_level)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":access_level", ACCESS_LEVEL_USERS);
    if (!query.exec()) {
        qDebug() << "Add user failed:" << query.lastError();
        return false;
    }

    return true;
}
