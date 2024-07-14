#ifndef GLOBAL_H
#define GLOBAL_H

//#include "httpsessionstore.h"
//#include "staticfilecontroller.h"

// Forward decleration for pointers of class
class StaticFileController;

// Define namespaces
using namespace QTWebApp;


// Define HTTP Status
#define HTTP_STATUS_OK                          200
#define HTTP_STATUS_BAD_REQUEST                 400
#define HTTP_STATUS_UNAUTHORIZED                401
#define HTTP_STATUS_NOT_FOUND                   404

// Define HTTP Status description
#define HTTP_STATUS_OK_DESCRIPTION              "OK"
#define HTTP_STATUS_BAD_REQUEST_DESCRIPTION     "Bad Request"
#define HTTP_STATUS_UNAUTHORIZED_DESCRIPTION    "Unauthorized"
#define HTTP_STATUS_NOT_FOUND_DESCRIPTION       "Not Found"



//extern HttpSessionStore* sessionStore;
extern StaticFileController* staticFileController;

#endif // GLOBAL_H
