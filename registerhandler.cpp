#include "registerhandler.h"
#include "global.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "databasehandler.h"
#include "jwthandler.h"
RegisterHandler::RegisterHandler(QObject *parent)
    : HttpRequestHandler(parent) {
    //
}


void RegisterHandler::service(HttpRequest &request, HttpResponse &response) {

    QString username,password;

    // check validation of JSON Format
    if(!JWT::checkJsonValidation(request.getBody(),"username",&username,"password",&password)){
        //if is not valid send bad status to requester
        response.setStatus(HTTP_STATUS_BAD_REQUEST,HTTP_STATUS_BAD_REQUEST_DESCRIPTION);
        return;
    }

    qDebug() << "username:" <<username <<"\npassword:"<<password;
    // Check User valid in DB or not
    if (!Database::validateUser(username,password)) {

        if (!Database::addUser(username,password))
        {
            response.setStatus(HTTP_STATUS_BAD_REQUEST,HTTP_STATUS_BAD_REQUEST_DESCRIPTION);
            response.write("",true);
            return;
        }
        auto token = JWT::generateJWT(username);

        // Create JSON to send JWT Token to front-end
        QJsonObject responseObj;
        responseObj["token"] = QString::fromStdString(token.toStdString());
        QJsonDocument responseDoc(responseObj);

        // Send JSON
        response.setStatus(HTTP_STATUS_OK,HTTP_STATUS_OK_DESCRIPTION);
        response.write(responseDoc.toJson(),true);
    }
    else {
        // if user invalid set status = UNAUTHORIZED(401)
        response.setStatus(HTTP_STATUS_BAD_REQUEST,HTTP_STATUS_BAD_REQUEST_DESCRIPTION);
        response.write("",true);
    }
}
