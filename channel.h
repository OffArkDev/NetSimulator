#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class Channel : public QGraphicsObject
{
Q_OBJECT
public:
    explicit Channel(QObject *parent = 0);
    ~Channel();


     void setConnections(int i, int o);
     QString getData();
     void setData(QString d);

     int in;
     int out;
     QString data;
     int x1, x2, y1, y2;


private:
     QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
     void getPosStart(QPointF p);
     void getPosEnd(QPointF p);

signals:
     void sceneUpdate();

};

#endif // CHANNEL_H
