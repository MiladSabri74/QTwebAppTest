#include "filecontroller.h"
#include <QMutexLocker>

QMutex fileController::mutex_;

fileController::fileController()
{

}

void fileController::setFileHandler(QTWebApp::StaticFileController* handler)
{
//       std::lock_guard<std::mutex> lock(mutex_);
    QMutexLocker locker(&fileController::mutex_);
    staticFileHandler = handler;
}

StaticFileController* fileController::getFileHandler()
{
    QMutexLocker locker(&fileController::mutex_);
    return staticFileHandler;
}


