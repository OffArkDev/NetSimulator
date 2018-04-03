#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"
#include "client.h"
#include "channel.h"
#include "mythread.h"


#include <QWidget>
#include <QGraphicsScene>


static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    s_number = 0;
    c_number = 0;
    ch_number = 0;

    //max numbers of servers, clients and channels
    s_n = 10;
    c_n = 10;
    ch_n = 10;

    item_number = 0;

    server = new Server[s_n];
    client = new Client[c_n];
    channel = new Channel[ch_n];



    this->resize(640,640);          //  размеры окна приложения
    this->setFixedSize(640,640);

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); // индексация элементов

    ui->graphicsView->resize(600,600);  //  размер graphicsView
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    //  рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    scene->setSceneRect(0,0,500,500);


}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_addServerButton_clicked()
{

    array[item_number] = "s " + QString::number(s_number);
    s_number++;

    server[s_number-1].item_number = item_number;
    item_number++;
    server[s_number-1].setPos(randomBetween(30, 470),
                 randomBetween(30, 470));
    scene->addItem(&server[s_number-1]);
    server[s_number-1].server_number = s_number;

}



void MainWindow::on_addClientServer_clicked()
{
    array[item_number] = "c " + QString::number(c_number);
    c_number++;
    client[c_number-1].item_number = item_number;
    item_number++;


    client[c_number-1].setPos(randomBetween(30, 470),
                 randomBetween(30, 470));
    scene->addItem(&client[c_number-1]);
    client[c_number-1].client_number = c_number;
}

void MainWindow::getSceneUpdate() {
    scene->update();
}

void MainWindow::on_addChannelButton_clicked()
{

    ch_number++;
    int in = ui->inSpinBox->value();
    int out = ui->outSpinBox->value();
    channel[ch_number-1].setConnections(in, out);

    int i = array[in].split(' ')[1].toInt();
    int o = array[out].split(' ')[1].toInt();

    bool isClient;

    if (array[in].split(' ')[0] == "c") {
        isClient = true;
    } else isClient = false;


    if (isClient) {
    connect(client[i].dialog_client, SIGNAL(sendData(QString, QString)), server[o].dialog, SLOT(getDataClient(QString,QString)));
    connect(client[i].dialog_client, SIGNAL(tryPassword(QString)), server[o].dialog, SLOT(recievePassword(QString)));
    connect(server[o].dialog, SIGNAL(acceptPassword(bool)), client[i].dialog_client, SLOT(recieveResultLogin(bool)));

    connect(client[i].dialog_client, SIGNAL(getData(QString)), server[o].dialog, SLOT(recieveDataPassword(QString)));
    connect(server[o].dialog, SIGNAL(sendData(QString)), client[i].dialog_client, SLOT(recieveData(QString)));

    connect(client[i].dialog_client, SIGNAL(tryAttack(QString,int,bool)), server[o].dialog, SLOT(getAttacked(QString,int,bool)));

    connect(client[i].dialog_client, SIGNAL(sendDDoSData(QString)), server[o].dialog, SLOT(getDDoSData(QString)));

    channel[ch_number-1].x1 = client[i].x();
    channel[ch_number-1].x2 = server[o].x();

    channel[ch_number-1].y1 = client[i].y();    
    channel[ch_number-1].y2 = server[o].y();

    connect(&client[i], SIGNAL(sendPos(QPointF)), &channel[ch_number-1], SLOT(getPosStart(QPointF)));
    connect(&server[o], SIGNAL(sendPos(QPointF)), &channel[ch_number-1], SLOT(getPosEnd(QPointF)));
    connect(&channel[ch_number-1], SIGNAL(sceneUpdate()), this, SLOT(getSceneUpdate()));
    scene->addItem(&channel[ch_number-1]);
    scene->update();

    } else {
        connect(server[i].dialog, SIGNAL(sendData(QString)), server[o].dialog, SLOT(recieveData(QString)));
        connect(server[i].dialog, SIGNAL(tryChanneledAttack(QString,int,bool)), server[o].dialog, SLOT(getAttacked(QString,int,bool)));

        channel[ch_number-1].x1 = server[i].x();
        channel[ch_number-1].y1 = server[i].y();
        channel[ch_number-1].x2 = server[o].x();
        channel[ch_number-1].y2 = server[o].y();

        connect(&server[i], SIGNAL(sendPos(QPointF)), &channel[ch_number-1], SLOT(getPosStart(QPointF)));
        connect(&server[o], SIGNAL(sendPos(QPointF)), &channel[ch_number-1], SLOT(getPosEnd(QPointF)));
        connect(&channel[ch_number-1], SIGNAL(sceneUpdate()), this, SLOT(getSceneUpdate()));
        scene->addItem(&channel[ch_number-1]);
        scene->update();
    }
}
