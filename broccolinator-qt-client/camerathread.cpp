#include "camerathread.h"
#include <QNetworkAccessManager>

void CameraThread::run()
{
    QNetworkAccessManager nam;

    connect(&nam,&QNetworkAccessManager::finished,this,&CameraThread::downloadFinished);

    for (;;)
    {
        const QUrl url = QUrl("http://192.168.1.3/image/jpeg.cgi");

        QNetworkRequest request(url);
        QNetworkReply* reply=nam.get(request);

        QNetworkReply::NetworkError error=reply->error();
        
        if (error!=QNetworkReply::NoError)
        {
            delete reply;
        }
        else
        {
            exec();
        }                
    }    
}

void CameraThread::downloadFinished(QNetworkReply* reply)
{
    emit frameReady(reply);
    quit();
}