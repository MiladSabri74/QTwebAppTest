#ifndef REGISTERHANDLER_H
#define REGISTERHANDLER_H

#include <QObject>
#include "httprequesthandler.h"


using namespace QTWebApp;

class RegisterHandler : public HttpRequestHandler
{
    Q_OBJECT
public:
    RegisterHandler(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
signals:

public slots:
};

#endif // REGISTERHANDLER_H
