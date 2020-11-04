#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H
#include <QThread>
#include <QNetworkReply>

class CameraThread : public QThread
{
    Q_OBJECT

    public:

        void run();

    signals:

        void frameReady(QNetworkReply *reply);

    private  slots: 

        void downloadFinished(QNetworkReply* reply);
};

#endif
