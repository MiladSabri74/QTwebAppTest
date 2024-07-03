#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include <QObject>
#include "httprequesthandler.h"

#include "maincontroller.h"
#include "logincontroller.h"
#include "registerhandler.h"

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
    RegisterHandler registerPage;
};

#endif // REQUESTMAPPER_H
