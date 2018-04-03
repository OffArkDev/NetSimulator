#ifndef MYTHREAD_H
#define MYTHREAD_H


#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0, bool b = false);
    void run();

    bool Stop;
    QString name;

signals:
    void valueChanged(int, QString);

public slots:

};

#endif // MYTHREAD_H
