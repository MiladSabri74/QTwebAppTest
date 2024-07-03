#include "logincontroller.h"
#include <QTime>
#include "global.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "databasehandler.h"
#include "jwthandler.h"

loginController::loginController(QObject* parent)
    : HttpRequestHandler(parent) {
    //
}

void loginController::service(HttpRequest &request, HttpResponse &response) {

    QString username,password;

    // check validation of JSON Format
    if(!JWT::checkJsonValidation(request.getBody(),"username",&username,"password",&password)){
        //if is not valid send bad status to requester
        response.setStatus(HTTP_STATUS_BAD_REQUEST,HTTP_STATUS_BAD_REQUEST_DESCRIPTION);
        return;
    }

    qDebug() << "username:" <<username <<"\npassword:"<<password;
    // Check User valid in DB or not
    if (Database::validateUser(username,password)) {

        auto token = JWT::generateJWT(username);

        qDebug() << "TOKEN" << token;
        // Create JSON to send JWT Token to front-end
        QJsonObject responseObj;
        responseObj["token"] = QString::fromStdString(token.toStdString());
        QJsonDocument responseDoc(responseObj);

         qDebug() << "JSON" << responseDoc.toJson();
        // Send JSON
        response.setStatus(HTTP_STATUS_OK,HTTP_STATUS_OK_DESCRIPTION);
        response.write(responseDoc.toJson(),true);
    }
    else {
        // if user invalid set status = UNAUTHORIZED(401)
        response.setStatus(HTTP_STATUS_UNAUTHORIZED,HTTP_STATUS_UNAUTHORIZED_DESCRIPTION);
        response.write("",true);
    }
}


