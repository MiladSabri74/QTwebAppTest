#ifndef REGISTERHANDLER_H
#define REGISTERHANDLER_H

#include <QObject>
#include "httprequesthandler.h"


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
