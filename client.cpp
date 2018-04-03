#include "client.h"
#include "dialog.h"

Client::Client(QObject *parent) :
    QGraphicsObject()
{

    dialog_client = new DialogClient();
    pixmap = QPixmap(":/img/Client.png");
}

Client::~Client()
{

}


QRectF Client::boundingRect() const
{
    return QRectF (-20,-20,40,40);
}

void Client::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    //painter->drawRect(-20,-20,40,40);
    painter->drawPixmap(-20,-20,40,40, pixmap);
    painter->drawText(boundingRect(), Qt::AlignBottom, QString::number(item_number));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Client::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
    emit sendPos(mapToScene(event->pos()));
    Q_UNUSED(event)
}

void Client::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void Client::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void Client::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    dialog_client->client_number = this->client_number;
    dialog_client->exec();
    Q_UNUSED(event)
}

QString Client::sendDatatoChannel() {
    return out_channel;
}


