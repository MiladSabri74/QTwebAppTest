
#include "databasehandler.h"
#include "requestmapper.h"
#include "jwthandler.h"

RequestMapper::RequestMapper(QObject* parent)
    : HttpRequestHandler(parent) {
    //
}


void RequestMapper::service(HttpRequest &request, HttpResponse &response) {
    QByteArray path=request.getPath();
    qDebug("RequestMapper: path=%s",path.data());


    if (path=="/login") {
        testPage.service(request, response);
    }
    else if (path=="/register") {
        registerPage.service(request, response);
    }
    else if (path=="/" || path=="/main") {
        samplePage.service(request, response);
    }
    else if (path.startsWith("/files")) {

        response.setStatus(HTTP_STATUS_UNAUTHORIZED,HTTP_STATUS_UNAUTHORIZED_DESCRIPTION);

        // Check JWT Token and user validation
        QString token = request.getHeader("jwt");
        JWT::checkTokenValidation(token);

        // Send Response OK
        response.setStatus(HTTP_STATUS_OK,HTTP_STATUS_OK_DESCRIPTION);
        staticFileController->service(request,response);

    }
    else {
        response.setStatus(HTTP_STATUS_NOT_FOUND,HTTP_STATUS_NOT_FOUND_DESCRIPTION);
        response.write("The URL is wrong, no such document.",true);
    }

    qDebug("RequestMapper: finished request");

}
