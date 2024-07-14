// General Libraries
#include <QCoreApplication>
#include <QSettings>
#include <QFile>
#include <QDir>

#include <jwt-cpp/jwt.h>

// libraires from QTWebApp
#include "httplistener.h"
#include "httprequesthandler.h"

// Custom files
#include "requestmapper.h"
#include "databasehandler.h"
//#include "global.h"

//
#include "filecontroller.h"

using namespace QTWebApp;
/*
 * this function use for searching in directories related to project
 * and return the address of setting file(*.ini file)
*/
QString searchConfigFile(QString settingFile) {
    QString binDir=QCoreApplication::applicationDirPath();
    QString appName=QCoreApplication::applicationName();
    //QString fileName("webapp1.ini");
    QString fileName = settingFile;

    QStringList searchList;
    searchList.append(binDir);
    searchList.append(binDir+"/etc");
    searchList.append(binDir+"/../etc");
    searchList.append(binDir+"/../"+appName+"/etc");     // for development with shadow build (Linux)
    searchList.append(binDir+"/../../"+appName+"/etc");  // for development with shadow build (Windows)
    searchList.append(QDir::rootPath()+"etc/opt");
    searchList.append(QDir::rootPath()+"etc");

    foreach (QString dir, searchList)
    {
        QFile file(dir+"/"+fileName);
        if (file.exists())
        {
            // The method QDir::canonicalPath() converts relative path names to the absolute form
            fileName=QDir(file.fileName()).canonicalPath();
            qDebug("CONFIG: Using config file %s",qPrintable(fileName));
            return fileName;
        }
    }

    // not found
    foreach (QString dir, searchList)
    {
        qWarning("CONFIG: %s/%s not found",qPrintable(dir),qPrintable(fileName));
    }
    qFatal("CONFIG: Cannot find config file %s",qPrintable(fileName));
    return nullptr;
}


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);


    // Find setting file and load it to listenerSettings object(if can not find crashed!)
    QString configFileName = searchConfigFile("webapp1.ini");
    qInfo("CONFIG: config file loaded\n");


    // Static file controller
    QSettings* fileSettings = new QSettings(configFileName,QSettings::IniFormat,&app);
    fileSettings->beginGroup("files");

    fileController fileHandler;
    fileHandler.setFileHandler(new StaticFileController(fileSettings,&app));

    qInfo("StaticFileController: File handler service is run now ...\n");


    Database::initializeDatabase();


    // Session store
    //    QSettings* sessionSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    //    sessionSettings->beginGroup("sessions");
    //    sessionStore=new HttpSessionStore(sessionSettings,&app);



    // Start the HTTP server

    QSettings* listenerSettings = new QSettings(configFileName,QSettings::IniFormat,&app);
    listenerSettings->beginGroup("listener");

    new QTWebApp::HttpListener(listenerSettings, new RequestMapper(&app), &app);

    return app.exec();
}
