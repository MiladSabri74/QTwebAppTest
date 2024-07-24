
#include "databasehandler.h"
#include "registercontroller.h"

bool getJSONParameter(QJsonDocument jsonDoc,const QString& key,QString* value);
QByteArray generateJWT(const QString& username,int accessLevel);

RegisterController::RegisterController(QObject *parent)
    : HttpRequestHandler(parent) {
    //
}


void RegisterController::service(HttpRequest &request, HttpResponse &response) {

    // define variables
    QString username,password;
    int userAccessLevel = ACCESS_LEVEL_ALL;

    QJsonObject responseObj;
    int validationErrorCode = NO_ERROR;

    // read JSON
    QJsonDocument jsonDoc = QJsonDocument::fromJson(request.getBody());

    // read parameters(username and password)
    if (!getJSONParameter(jsonDoc,JSON_KEY_USERNAME,&username) || !getJSONParameter(jsonDoc,JSON_KEY_PASSWORD,&password)){
        validationErrorCode = ERROR_JSON;
    }
    else{
        // check info from db and return user access level
        if(!Database::checkExistanceUser(username,1)){
            if (!Database::addUser(username,password))
            {
                validationErrorCode = ERROR_DB;
            }
        }
        else{
            validationErrorCode = ERROR_USER_EXIST;
        }
    }

    // prepare response to send
    switch (validationErrorCode) {
    // NO ERROR
    case NO_ERROR:{
        //generate token
        //use username as subject and userAccessLevel in payload-claim dedicated via ("access-level")
        auto token = generateJWT(username,userAccessLevel);

        //create JSON parameters
        responseObj[JSON_KEY_STATUS] = QString::fromStdString(JSON_VALUE_STATUS_OK);
        responseObj[JSON_KEY_MESSAGE] = QString::fromStdString("User registered successfully");
        responseObj[JSON_KEY_TOKEN] = QString::fromStdString(token.toStdString());

        //set status of response
        response.setStatus(HTTP_STATUS_OK,HTTP_STATUS_OK_DESCRIPTION);
        break;
    }
    // invalid json parameter
    case ERROR_JSON:
        //create JSON parameters
        responseObj[JSON_KEY_STATUS] = QString::fromStdString(JSON_VALUE_STATUS_FAIL);
        responseObj[JSON_KEY_MESSAGE] = JSON_MESSAGE_REPORT_ERROR_CODE +
                                        QString::number(JSON_ERROR_CODE_INVALID_PARAMETER);

        //set status of response
        response.setStatus(HTTP_STATUS_BAD_REQUEST,HTTP_STATUS_BAD_REQUEST_DESCRIPTION);
        break;

    // can not add user into db
    case ERROR_DB:
        //create JSON parameters
        responseObj[JSON_KEY_STATUS] = QString::fromStdString(JSON_VALUE_STATUS_FAIL);
        responseObj[JSON_KEY_MESSAGE] = JSON_MESSAGE_REPORT_ERROR_CODE +
                                        QString::number(JSON_ERROR_CODE_REGISTER_DATABASE);

        //set status of response
        response.setStatus(HTTP_STATUS_BAD_REQUEST,HTTP_STATUS_BAD_REQUEST_DESCRIPTION);

    // user eexist in db
    case ERROR_USER_EXIST:
        //create JSON parameters
        responseObj[JSON_KEY_STATUS] = QString::fromStdString(JSON_VALUE_STATUS_FAIL);
        responseObj[JSON_KEY_MESSAGE] = JSON_MESSAGE_REPORT_ERROR_CODE +
                                        QString::number(JSON_ERROR_CODE_EXIST_USER_DB);

        //set status of response
        response.setStatus(HTTP_STATUS_BAD_REQUEST,HTTP_STATUS_BAD_REQUEST_DESCRIPTION);
    default:
        break;
    }

    //send JSON document as response
    QJsonDocument responseDoc(responseObj);
    response.write(responseDoc.toJson(),true);
}


