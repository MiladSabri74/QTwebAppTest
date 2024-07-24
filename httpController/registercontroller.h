#ifndef REGISTERHANDLER_H
#define REGISTERHANDLER_H

#include <QObject>
#include "httprequesthandler.h"

#define NO_ERROR            0
#define ERROR_JSON          1
#define ERROR_DB            2
#define ERROR_USER_EXIST    3



using namespace QTWebApp;

class RegisterController : public HttpRequestHandler
{
    Q_OBJECT
public:
    RegisterController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
signals:

public slots:
};

#endif // REGISTERHANDLER_H
