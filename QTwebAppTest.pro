QT -= gui
QT += network
QT += sql

CONFIG += c++11 console
CONFIG -= app_bundle
CONFIG += precompile_header

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#include(../QtWebApp/QtWebApp/httpserver/httpserver.pri)
#include($$PWD/QtWebApp/QtWebApp/httpserver/httpserver.pri)

include($$PWD/httpController/httpController.pri)

#JWT

# Include path for jwt-cpp
INCLUDEPATH += $$PWD/jwt-cpp/include

# Include path for OpenSSL headers (if not already included)
INCLUDEPATH += /usr/include/openssl

# Link OpenSSL libraries (if not already linked)
LIBS += -L/usr/lib -lssl -lcrypto

# Define Precompiled header
PRECOMPILED_HEADER = predefinedheaders.h


OTHER_FILES += etc/webapp1.ini

SOURCES += main.cpp \
    #logincontroller.cpp \
    #maincontroller.cpp \
    databasehandler.cpp \
    #requestmapper.cpp \
    #global.cpp \
    #registerhandler.cpp
   # filecontroller.cpp

HEADERS += \
    #requestmapper.h \
    #logincontroller.h \
    #maincontroller.h \
    databasehandler.h \
    #registerhandler.h \
    definition.h \
    predefinedheaders.h \
    #filecontroller.h


