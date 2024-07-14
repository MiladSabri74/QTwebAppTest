INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += network

# Enable very detailed debug messages when compiling the debug version
CONFIG(debug, debug|release) {
    DEFINES += SUPERVERBOSE
}

include(../QtWebApp/QtWebApp/httpserver/httpserver.pri)


HEADERS +=\
	 $$PWD/requestmapper.h \
  	 $$PWD/logincontroller.h \
  	 $$PWD/maincontroller.h \
	 $$PWD/registerhandler.h

SOURCES += \
         $$PWD/requestmapper.cpp\
         $$PWD/logincontroller.cpp\
         $$PWD/maincontroller.cpp \
         $$PWD/registerhandler.cpp

