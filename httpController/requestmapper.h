#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include <QObject>
#include "httprequesthandler.h"

#include "maincontroller.h"
#include "logincontroller.h"
#include "registercontroller.h"

using namespace QTWebApp;

class RequestMapper : public HttpRequestHandler

{
    Q_OBJECT
public:
    RequestMapper(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
private:
    MainController samplePage;
    loginController testPage;
    RegisterController registerPage;

    bool isJSON(const QByteArray& input);

    bool isTokenExist(const QByteArray& tokenJWT);
    bool isTokenValid(const QByteArray& tokenJWT,QString* username,int* userAccessLevel);
    void decodeToken(bool& isValid,const QByteArray& decoded);

    int minAllowedAccessLevel(const QByteArray& path);

    int readAccessLevel(const QByteArray& input);
    void sendShortResponse(HttpResponse &response,int status);
};

#endif // REQUESTMAPPER_H
