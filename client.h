#ifndef CLIENT_H
#define CLIENT_H

#include "dialogclient.h"
#include "channel.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>


class Client : public QGraphicsObject
{

    Q_OBJECT
public:
        explicit Client(QObject *parent = 0);
        ~Client();

        int item_number;
        int client_number;
        QString out_channel;
        QPixmap pixmap;

         DialogClient *dialog_client;
         Channel *channel;


    //graphic

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

signals:
    void sendPos(QPointF p);

private:
    QString sendDatatoChannel();


};

#endif // CLIENT_H
