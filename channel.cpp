#include "channel.h"

Channel::Channel(QObject *parent) :
    QGraphicsObject()
{

}

Channel::~Channel()
{

}

QRectF Channel::boundingRect() const
{
    return QRectF (x1, y1, x2, y2);
}

void Channel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->drawLine(x1, y1, x2, y2);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Channel::setConnections(int i, int o){
    in = i;
    out = o;
}

void Channel::getPosStart(QPointF p) {
    x1 = p.x();
    y1 = p.y();
    this->prepareGeometryChange();
    //I didn't find another way to solve the problem of drawing a line
    emit sceneUpdate();
}

void Channel::getPosEnd(QPointF p){
    x2 = p.x();
    y2 = p.y();
    this->prepareGeometryChange();
    //I didn't find another way to solve the problem of drawing a line
    emit sceneUpdate();
}



