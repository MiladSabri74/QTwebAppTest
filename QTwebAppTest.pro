QT -= gui
QT += network
QT += sql

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../QtWebApp/QtWebApp/httpserver/httpserver.pri)

#JWT
#INCLUDEPATH += $$PWD/jwt

#INCLUDEPATH += $$PWD/jwt-cpp/include
##LIBS += /usr/local/lib -lssl -lcrypto

## Add include path for the OpenSSL headers
#INCLUDEPATH += /usr/include/openssl

# Add library path for the OpenSSL libraries
#LIBS += -L/usr/lib -lssl -lcrypto
#required for JWT:
#unix{
#    LIBS += -L$$PWD/../../../othersource/openssl-linux/lib -lssl
#    LIBS += -L$$PWD/../../../othersource/openssl-linux/lib -lcrypto
#    LIBS += -ladclient
#}


# Include path for jwt-cpp
INCLUDEPATH += $$PWD/jwt-cpp/include
#INCLUDEPATH += $$PWD/json/include/nlohmann
#INCLUDEPATH += $$PWD/json/include

# Include path for OpenSSL headers (if not already included)
INCLUDEPATH += /usr/include/openssl


# Link OpenSSL libraries (if not already linked)
LIBS += -L/usr/lib -lssl -lcrypto



OTHER_FILES += etc/webapp1.ini

SOURCES += main.cpp \
    logincontroller.cpp \
    maincontroller.cpp \
    databasehandler.cpp \
    jwthandler.cpp \
    requestmapper.cpp \
    global.cpp \
    registerhandler.cpp

HEADERS += \
    requestmapper.h \
    logincontroller.h \
    maincontroller.h \
    global.h \
    databasehandler.h \
    jwthandler.h \
    registerhandler.h


