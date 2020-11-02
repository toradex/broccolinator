#include "mainwindow.h"
#include "camerathread.h"
#include "socketthread.h"

#include <QObject>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainwindow;

    CameraThread camerathread;
    SocketThread socketthread;

    mainwindow.show();

    QObject::connect(&camerathread,&CameraThread::frameReady,&mainwindow,&MainWindow::showFrame);
    QObject::connect(&socketthread,&SocketThread::error,&mainwindow,&MainWindow::showError);
    QObject::connect(&socketthread,&SocketThread::data,&mainwindow,&MainWindow::showData);

    camerathread.start();    
    socketthread.start();
    return app.exec();
}
