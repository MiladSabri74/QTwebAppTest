#ifndef GLOBAL_H
#define GLOBAL_H

#include "httpsessionstore.h"
#include "staticfilecontroller.h"


#define HTTP_STATUS_OK                          200
#define HTTP_STATUS_BAD_REQUEST                 400
#define HTTP_STATUS_UNAUTHORIZED                401
#define HTTP_STATUS_NOT_FOUND                   404


#define HTTP_STATUS_OK_DESCRIPTION              "OK"
#define HTTP_STATUS_BAD_REQUEST_DESCRIPTION     "Bad Request"
#define HTTP_STATUS_UNAUTHORIZED_DESCRIPTION    "Unauthorized"
#define HTTP_STATUS_NOT_FOUND_DESCRIPTION       "Not Found"

using namespace QTWebApp;

//extern HttpSessionStore* sessionStore;
extern StaticFileController* staticFileController;
#endif // GLOBAL_H
