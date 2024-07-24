#ifndef DEFINITION_H
#define DEFINITION_H


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

#define JSON_KEY_ACCESS_LEVEL                   "access_level"
#define JSON_KEY_MESSAGE                        "message"
#define JSON_KEY_STATUS                         "status"
#define JSON_KEY_TOKEN                          "token"

#define JSON_KEY_DATA                           "data"
#define JSON_KEY_FILE_NAME                      "file_name"

#define JSON_KEY_USERNAME                       "username"
#define JSON_KEY_PASSWORD                       "password"

#define ACCESS_LEVEL_ALL                        0
#define ACCESS_LEVEL_USERS                      1
#define ACCESS_LEVEL_ADMIN                      2
#define ACCESS_LEVEL_OWNER                      3

#define MAX_ACCESS_LEVEL                        3

#define JSON_VALUE_MESSAGE_INVALID              "process can't done"
#define JSON_VALUE_MESSAGE_VALID                "process done successfully"

#define JSON_VALUE_STATUS_OK                    "success"
#define JSON_VALUE_STATUS_FAIL                  "failure"


#define JSON_ERROR_CODE_INVALID_FORMAT          1
#define JSON_ERROR_CODE_INVALID_ACCESS_LEVEL    2
#define JSON_ERROR_CODE_INVALID_JWT_TOKEN       3
#define JSON_ERROR_CODE_INVALID_PARAMETER       4
#define JSON_ERROR_CODE_INVALID_USER            5
#define JSON_ERROR_CODE_REGISTER_DATABASE       6
#define JSON_ERROR_CODE_EXIST_USER_DB           7

#define JSON_ERROR_CODE_FILE_NOT_OPEN           8
#define JSON_ERROR_CODE_FILE_NOT_EXIST          9
#define JSON_ERROR_CODE_FILE_WRITTING           10

#define JSON_MESSAGE_REPORT_ERROR_CODE          "ERROR Code : "
#endif // DEFINITION_H
