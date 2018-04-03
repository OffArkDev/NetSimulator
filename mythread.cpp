#include "mythread.h"
#include <QDebug>
#include <QMutex>

MyThread::MyThread(QObject *parent, bool b) :
    QThread(parent), Stop(b)
{
}


void MyThread::run()
{
    if (name == "" && name == 0) name = "null";
    for(int i = 0; i <= 100; i++)
    {
       QMutex mutex;
       mutex.lock();
        if(this->Stop) break;
        mutex.unlock();
        emit valueChanged(i, name);
        this->msleep(500);
    }
}
