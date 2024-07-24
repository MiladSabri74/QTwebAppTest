
#include "databasehandler.h"
#include "logincontroller.h"

bool getJSONParameter(QJsonDocument jsonDoc,const QString& key,QString* value);
QByteArray generateJWT(const QString& username,int accessLevel);

loginController::loginController(QObject* parent)
    : HttpRequestHandler(parent) {
    //
}

void loginController::service(HttpRequest &request, HttpResponse &response) {
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
        if(!Database::validateUser(username,password,&userAccessLevel)){
            validationErrorCode = ERROR_USER_NOT_EXIST;
        }
    }

    // send response
    switch (validationErrorCode) {
    // NO ERROR
    case NO_ERROR:{
        //generate token
        //use username as subject and userAccessLevel in payload-claim dedicated via ("access-level")
        auto token = generateJWT(username,userAccessLevel);

        //create JSON parameters
        responseObj[JSON_KEY_STATUS] = QString::fromStdString(JSON_VALUE_STATUS_OK);
        responseObj[JSON_KEY_MESSAGE] = QString::fromStdString("User login successfully");
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

    // invalid user
    case ERROR_USER_NOT_EXIST:
       //create JSON parameters
       responseObj[JSON_KEY_STATUS] = QString::fromStdString(JSON_VALUE_STATUS_FAIL);
       responseObj[JSON_KEY_MESSAGE] = JSON_MESSAGE_REPORT_ERROR_CODE +
                                       QString::number(JSON_ERROR_CODE_INVALID_USER);

       //set status of response
       response.setStatus(HTTP_STATUS_UNAUTHORIZED,HTTP_STATUS_UNAUTHORIZED_DESCRIPTION);
    default:
        break;
    }

    //send JSON document as response
    QJsonDocument responseDoc(responseObj);
    response.write(responseDoc.toJson(),true);
}

QByteArray generateJWT(const QString& username,int accessLevel) {

    const std::string SECRET_KEY = "NovinCompany";
    auto now = std::chrono::system_clock::now();
    auto expires_at = now + std::chrono::hours(1);

    auto token = jwt::create()
            .set_issuer("auth0")
            .set_type("JWS")
            .set_subject(username.toStdString())
            .set_payload_claim(JSON_KEY_ACCESS_LEVEL, jwt::claim(std::to_string(accessLevel)))
            .set_expires_at(expires_at)
            .sign(jwt::algorithm::hs256{SECRET_KEY});

    return QByteArray::fromStdString(token);
}
bool getJSONParameter(QJsonDocument jsonDoc,const QString& key,QString* value)
{
    QJsonObject jsonObj = jsonDoc.object();
    if (!jsonObj.contains(key)) {
        qDebug() << "JSON Handler : Missing key!" ;
        return false;
    }
    value->append(jsonObj[key].toString());
    return true;
}
