#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <QObject>
#include "httprequesthandler.h"


using namespace QTWebApp;

class loginController : public HttpRequestHandler

{
    Q_OBJECT
public:
    loginController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // TESTCONTROLLER_H
