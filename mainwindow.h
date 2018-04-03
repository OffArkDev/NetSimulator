#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "server.h"
#include "client.h"
#include "channel.h"
#include "dialogclient.h"
#include "dialog.h"
#include "mythread.h"

#include <QMainWindow>
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_addServerButton_clicked();

    void on_addClientServer_clicked();

    void on_addChannelButton_clicked();
    void getSceneUpdate();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;

    Server *server;
    int s_number;
    Client *client;
    int c_number;
    Channel *channel;
    int ch_number;


    int s_n;
    int c_n;
    int ch_n;

    int item_number;
    QString array[20];


signals:


};

#endif // MAINWINDOW_H
