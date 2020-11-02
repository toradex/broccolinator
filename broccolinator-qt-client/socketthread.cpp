#include <socketthread.h>
#include <QLocalSocket>
#include <QJsonDocument>
#include <QJsonObject>

#define SERVER_NAME "/tmp/broccolinator_output"
#define BUFFER_SIZE 1024

void SocketThread::run()
{
    QLocalSocket socket;

    socket.connectToServer(SERVER_NAME);
    socket.waitForConnected();

    for (;;)
    {
        socket.waitForReadyRead();
        QByteArray rawmsg=socket.read(1024);
        QJsonDocument json=QJsonDocument::fromJson(rawmsg);
        QJsonObject   msg=json.object();

        QString type=msg.value("type").toString();

        if (type=="error")
        {
            emit error();
        }
        else if (type=="measure")
        {
           QString tag=msg.value("tag").toString();
           int weight=msg.value("weight").toInt();

           emit data(tag,weight);
        }
    }
}