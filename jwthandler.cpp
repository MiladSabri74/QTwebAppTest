#include <chrono>

#include "databasehandler.h"

#include <jwt-cpp/jwt.h>
#include "jwthandler.h"


bool JWT::checkTokenValidation(const QString &token)
{
    // Verify a JWT token
    auto decoded = jwt::decode(token.toStdString());
    // check user is exist or not

    if(!Database::checkExistanceUser(QString::fromStdString(decoded.get_subject())))
    {
        qDebug() << "DB: USER dosen't exsited in database" ;
    }

    auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{"NovinCompany"})
            .with_issuer("auth0");

    verifier.verify(decoded);

    return true;
}

QByteArray JWT::generateJWT(const QString& username) {

    const std::string SECRET_KEY = "NovinCompany";
    auto now = std::chrono::system_clock::now();
    auto expires_at = now + std::chrono::hours(1);

    auto token = jwt::create()
            .set_issuer("auth0")
            .set_type("JWS")
            .set_subject(username.toStdString())
            .set_expires_at(expires_at)
            .sign(jwt::algorithm::hs256{SECRET_KEY});

    return QByteArray::fromStdString(token);
}


bool JWT::checkJsonValidation(const QByteArray& body,const QString& param1,QString* value1)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(body);
    if (!jsonDoc.isObject()) {
        qDebug() << "Invalid JSON format" ;
        return false;
    }
    QJsonObject jsonObj = jsonDoc.object();
    if (!jsonObj.contains(param1)) {
        qDebug() << "Missing vaildation token or text" ;
        return false;
    }
    else
    {
        value1->append(jsonObj[param1].toString());
    }
    return true;
}

bool JWT::checkJsonValidation(const QByteArray& body,const QString& param1,QString* value1,const QString& param2,QString* value2)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(body);
    if (!jsonDoc.isObject()) {
        qDebug() << "Invalid JSON format" ;
        return false;
    }

    QJsonObject jsonObj = jsonDoc.object();
    if (!jsonObj.contains(param1) || !jsonObj.contains(param2)) {
        qDebug() << "Missing param1 or param2" ;
        return false;
    }
    else
    {
        value1->append(jsonObj[param1].toString());
        value2->append(jsonObj[param2].toString());
    }
    return true;
}
