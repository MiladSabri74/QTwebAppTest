#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include "staticfilecontroller.h"
#include <memory>
#include <QMutex>

using namespace QTWebApp;

class fileController
{
public:
    
    fileController();

    void setFileHandler(StaticFileController *handler);
    StaticFileController* getFileHandler();

private:
    inline static StaticFileController* staticFileHandler = nullptr;
    static QMutex mutex_;
};


#endif // FILECONTROLLER_H
