#include "databasehandler.h"

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



bool Database::validateUser(const QString& username, const QString& password) {
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Database query failed:" << query.lastError();
        return false;
    }

    if (query.next()) {
        QString storedPassword = query.value(0).toString();
        return storedPassword == password;
    }

    return false;
}

bool Database::checkExistanceUser(const QString& username) {
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Database query failed:" << query.lastError();
        return false;
    }

    return true;
}

bool Database::addUser(const QString& username, const QString& password) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Add user failed:" << query.lastError();
        return false;
    }

    return true;
}
