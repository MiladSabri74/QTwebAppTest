
#include "databasehandler.h"
#include "requestmapper.h"
#include "filecontroller.h"

RequestMapper::RequestMapper(QObject* parent)
    : HttpRequestHandler(parent) {
    //
}


void RequestMapper::service(HttpRequest &request, HttpResponse &response) {

    /* ---------------------- define variables ---------------------- */
    // request info
    QByteArray bodyRequest = request.getBody();
    QByteArray tokenJWT = request.getHeader(JSON_KEY_TOKEN);
    QByteArray pathRequest = request.getPath();

    int allowedAccessLevel = ACCESS_LEVEL_ALL;
    // user parameter
    int userAccessLevel = ACCESS_LEVEL_ALL;
    QString username = "";

    /* ---------------------- debug erea ---------------------------- */
    qDebug("RequestMapper: path=%s",pathRequest.data());
    //qDebug("RequestMapper: tokenJWT=%s",tokenJWT.data());

    /* ---------------------- request validation -------------------- */
    //check request has json in the body
    if(!isJSON(bodyRequest)){
        sendShortResponse(response,JSON_ERROR_CODE_INVALID_FORMAT);
    }

    //check JWT and header of request
    //calculate access Level of user
    if(isTokenExist(tokenJWT)){
        if (!isTokenValid(tokenJWT,&username,&userAccessLevel)) {
            return;
        }
        qDebug() << "RequestMapper: username = " <<username << "access-level =" <<userAccessLevel;
    }

    /* ---------------------- service Handler ----------------------- */
    //service handlers access abillity base on

    //login page
    if (pathRequest=="/login") {
        allowedAccessLevel = ACCESS_LEVEL_ALL;
        if(userAccessLevel >= allowedAccessLevel) {
            qDebug("RequestMapper: RUN login page");
            testPage.service(request, response);
        }
    }
    //register page
    else if (pathRequest=="/register" ) {
        allowedAccessLevel = ACCESS_LEVEL_ALL;
        if(userAccessLevel >= allowedAccessLevel) {
            qDebug("RequestMapper: RUN register page");
            registerPage.service(request, response);
        }
    }

    //main page
    else if (pathRequest=="/" || pathRequest=="/main") {
        allowedAccessLevel = ACCESS_LEVEL_USERS;
        if(userAccessLevel >= allowedAccessLevel) {
            qDebug("RequestMapper: RUN main page");
            samplePage.service(request, response);
        }
    }

    //handle static files
    else if (pathRequest.startsWith("/files") ) {

        allowedAccessLevel = ACCESS_LEVEL_ADMIN;
        if(userAccessLevel >= allowedAccessLevel) {
            qDebug("RequestMapper: RUN handle static files");
            // Send Response OK
            response.setStatus(HTTP_STATUS_OK,HTTP_STATUS_OK_DESCRIPTION);
            fileController fc;
            fc.getFileHandler()->service(request,response);
        }
    } else {
        qDebug("RequestMapper: PART ELSE");
        response.setStatus(HTTP_STATUS_NOT_FOUND,HTTP_STATUS_NOT_FOUND_DESCRIPTION);
        //response.write("The URL is wrong, no such document.",true);
         response.write("",true);
    }

    qDebug("RequestMapper: allowedAccessLevel= %d",allowedAccessLevel);
    qDebug("RequestMapper: userAccessLevel= %d",userAccessLevel);

    if (allowedAccessLevel > userAccessLevel) {
        qDebug("RequestMapper: PART IF");
        response.setStatus(HTTP_STATUS_UNAUTHORIZED,HTTP_STATUS_UNAUTHORIZED_DESCRIPTION);
    }
    qDebug("RequestMapper: finished request");
}

bool RequestMapper::isJSON(const QByteArray& input)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(input);
    if (!jsonDoc.isObject()) {
        qDebug() << "Invalid JSON format" ;
        return false;
    }
    return true;
}

bool RequestMapper::isTokenValid(const QByteArray& token,QString* username,int* userAccessLevel)
{
    // Verify a JWT token
    auto decoded = jwt::decode(token.toStdString());

    auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{"NovinCompany"})
            .with_issuer("auth0");

    verifier.verify(decoded);

    //extract user parameter from Token
    *username = QString::fromStdString(decoded.get_subject());
    *userAccessLevel = QString::fromStdString(decoded.get_payload_claim("access_level").as_string()).toInt();


    // check username and access-level of user with database
    if(!Database::checkExistanceUser(QString::fromStdString(decoded.get_subject()),*userAccessLevel))
    {
        qDebug() << "RequestMapper: <isTokenValid> user invalid" ;
        return false;
    }

    return true;
}


void RequestMapper::sendShortResponse(HttpResponse &response,int status){

    QJsonObject responseObj;

    response.setStatus(status == 0 ? HTTP_STATUS_OK : HTTP_STATUS_BAD_REQUEST,
                       status == 0 ? HTTP_STATUS_OK_DESCRIPTION : HTTP_STATUS_BAD_REQUEST_DESCRIPTION);

    responseObj[JSON_KEY_STATUS] = QString::fromStdString(status == 0 ?  JSON_VALUE_STATUS_OK : JSON_VALUE_STATUS_FAIL);
    responseObj[JSON_KEY_MESSAGE] = (status == 0 ?  JSON_VALUE_MESSAGE_VALID : JSON_MESSAGE_REPORT_ERROR_CODE + QString::number(status) );
    QJsonDocument responseDoc(responseObj);
    response.write(responseDoc.toJson());
}

int RequestMapper::readAccessLevel(const QByteArray& input){
    QJsonDocument jsonDoc = QJsonDocument::fromJson(input);
    int accessLevel = -1;
    bool isOK = true;

    QJsonObject jsonObj = jsonDoc.object();
    if (!jsonObj.contains(JSON_KEY_ACCESS_LEVEL)) {
        qDebug() << "Missing send of access-level request" ;
        return accessLevel;
    }
    accessLevel = jsonObj[JSON_KEY_ACCESS_LEVEL].toString().toInt(&isOK,10);
    if(!isOK || accessLevel > MAX_ACCESS_LEVEL)
    {
        return -1;
    }
    return accessLevel;
}


bool RequestMapper::isTokenExist(const QByteArray& tokenJWT){
    if(tokenJWT.isEmpty()){
        return false;
    }
    return true;
}

int RequestMapper::minAllowedAccessLevel(const QByteArray& path){

}
