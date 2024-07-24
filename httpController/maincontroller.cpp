#include "databasehandler.h"
#include "maincontroller.h"

bool getJSONParameter(QJsonDocument jsonDoc,const QString& key,QString* value);
int writeDataInFile(QString& requestPath,QString& data);
void sendErrorHandler(HttpResponse &response,QJsonObject& responseObj,int validationErrorCode);

MainController::MainController(QObject* parent)
    : HttpRequestHandler(parent) {
    //
}


void MainController::service(HttpRequest &request, HttpResponse &response) {

    // define variables
    QString dataInput ="";
    QString fileName ="";

    QJsonObject responseObj;
    int validationErrorCode = 0;


    // read JSON
    QJsonDocument jsonDoc = QJsonDocument::fromJson(request.getBody());

    // read parameters(data)
    if (!getJSONParameter(jsonDoc,JSON_KEY_DATA,&dataInput) || !getJSONParameter(jsonDoc,JSON_KEY_FILE_NAME,&fileName) ){
        validationErrorCode = 1;
    }

    // try to write data into file
    validationErrorCode = writeDataInFile(fileName,dataInput);

    // send response
    if(validationErrorCode == 0 )
    {
        //create JSON parameters
        responseObj[JSON_KEY_STATUS] = QString::fromStdString(JSON_VALUE_STATUS_OK);
        responseObj[JSON_KEY_MESSAGE] = QString::fromStdString(JSON_VALUE_MESSAGE_VALID);
        //set status of response
        response.setStatus(HTTP_STATUS_OK,HTTP_STATUS_OK_DESCRIPTION);
    }
    else
    {
        sendErrorHandler(response,responseObj,validationErrorCode);
    }

    //send JSON document as response
    QJsonDocument responseDoc(responseObj);
    response.write(responseDoc.toJson(),true);

}

int writeDataInFile(QString& requestPath,QString& dataInput){
    int validationErrorCode = 0;

    if (dataInput.isEmpty()) {
        validationErrorCode = 1;
    }
    else if(requestPath == "input.txt"){
        QFile file("/home/novin/Projects/QT-Projects/server-side/QTwebAppTest/docroot/files/input.txt");
        if (file.open(QIODevice::ReadWrite  |QIODevice::Append| QIODevice::Text)){
            qDebug() << "Main Controller: File opened" << requestPath << ".";
            file.seek(file.size());
            if(file.write(dataInput.toUtf8()+"\n")){
                qDebug() << "Main Controller: Data "<<dataInput << " write at the end of" <<requestPath << ".";
            }
            else{
                qDebug() << "Main Controller: can not write data "<<dataInput << "into " <<requestPath << ".";
                validationErrorCode = 4;
            }
        }
        else{
            qDebug() << "Main Controller: can not open file"<<requestPath << ".";
            validationErrorCode = 2;
        }
    }
    else{
        validationErrorCode = 3;
    }

    return validationErrorCode;
}

void sendErrorHandler(HttpResponse &response,QJsonObject& responseObj,int validationErrorCode){

    //create JSON parameters
    responseObj[JSON_KEY_STATUS] = QString::fromStdString(JSON_VALUE_STATUS_FAIL);
    //set status of response
    response.setStatus(HTTP_STATUS_BAD_REQUEST,HTTP_STATUS_BAD_REQUEST_DESCRIPTION);
    switch (validationErrorCode) {

    case 1:
        //create JSON parameters
        responseObj[JSON_KEY_MESSAGE] = JSON_MESSAGE_REPORT_ERROR_CODE +
                QString::number(JSON_ERROR_CODE_INVALID_PARAMETER);
        break;

    case 2:
        //create JSON parameters
        responseObj[JSON_KEY_MESSAGE] = JSON_MESSAGE_REPORT_ERROR_CODE +
                QString::number(JSON_ERROR_CODE_FILE_NOT_OPEN);
        break;
    case 3:
        //create JSON parameters
        responseObj[JSON_KEY_MESSAGE] = JSON_MESSAGE_REPORT_ERROR_CODE +
                QString::number(JSON_ERROR_CODE_FILE_NOT_EXIST);
        break;
    case 4:
        //create JSON parameters
        responseObj[JSON_KEY_MESSAGE] = JSON_MESSAGE_REPORT_ERROR_CODE +
                QString::number(JSON_ERROR_CODE_FILE_WRITTING);
        break;
    default:
        responseObj[JSON_KEY_MESSAGE] = JSON_VALUE_MESSAGE_INVALID;
        break;

    }

}


