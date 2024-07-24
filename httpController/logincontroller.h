#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <QObject>
#include "httprequesthandler.h"

#define NO_ERROR                0
#define ERROR_JSON              1
#define ERROR_USER_NOT_EXIST    2

using namespace QTWebApp;

class loginController : public HttpRequestHandler

{
    Q_OBJECT
public:
    loginController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // TESTCONTROLLER_H
