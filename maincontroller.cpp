#include "maincontroller.h"
#include <QDebug>

#include "global.h"
#include "databasehandler.h"
#include "jwthandler.h"

MainController::MainController(QObject* parent)
    : HttpRequestHandler(parent) {
    //
}


void MainController::service(HttpRequest &request, HttpResponse &response) {

    // Check JWT Token and user validation
    QString token = request.getHeader("jwt");
    JWT::checkTokenValidation(token);


    // Check correctness of reciceved JSON and export parameters
    QString inputLine;
    if(!JWT::checkJsonValidation(request.getBody(),"inputLine",&inputLine))
    {
        //if is not valid send bad status to requester
        response.setStatus(HTTP_STATUS_BAD_REQUEST,HTTP_STATUS_BAD_REQUEST_DESCRIPTION);
        return;
    }
    // Open File and write into input.txt file
    if (!inputLine.isEmpty()) {
        QFile file("/home/novin/Documents/Projects/ServerApps/QTwebAppTest/docroot/files/input.txt");
        if (file.open(QIODevice::ReadWrite  |QIODevice::Append| QIODevice::Text))
            qDebug("file Open!");
        else
            qDebug("file not Open!");
        file.seek(file.size());
        if(file.write(inputLine.toUtf8()+"\n"))
            qDebug("written Completed!");
        else
            qDebug("Dont Write!");
    }

    //response OK
    response.setStatus(HTTP_STATUS_OK,HTTP_STATUS_OK_DESCRIPTION);
}