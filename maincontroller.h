#ifndef SAMPLECONTROLLER_H
#define SAMPLECONTROLLER_H

#include "httprequesthandler.h"

using namespace QTWebApp;

class MainController : public HttpRequestHandler
{
    Q_OBJECT
public:
    MainController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // SAMPLECONTROLLER_H
