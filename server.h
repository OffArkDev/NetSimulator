#ifndef SERVER_H
#define SERVER_H

#include "dialog.h"
#include "channel.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QPixmap>

class Server : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    ~Server();

    int server_number;
    int item_number;
    QString in_channel;
    QString out_channel;
    QPixmap pixmap;

    Dialog *dialog;
    Channel *channel;

public slots:


signals:
    void sendPos(QPointF p);


private:

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);


    QString data;
    QString password;
    int max_req;


public:

    void send_status();
    QString send_data();
    bool try_password(QString out_data);
    void set_password(QString out_data);
    QString get_data(QString _password);
};

#endif // SERVER_H
