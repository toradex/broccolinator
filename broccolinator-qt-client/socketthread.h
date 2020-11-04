#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H
#include <QThread>


class SocketThread : public QThread
{
    Q_OBJECT

    public:

        void run();

    signals:

        void data(QString tag,int weight);
        void error();
};

#endif
