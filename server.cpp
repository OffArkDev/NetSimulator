#include "server.h"
#include "dialog.h"

Server::Server(QObject *parent) :
    QGraphicsObject()
{
    dialog = new Dialog();
    pixmap = QPixmap(":/img/Server.png");
}

Server::~Server()
{

}

void Server::set_password(QString out_data) {
    password = out_data;
}
bool Server::try_password(QString out_data) {
    if (out_data == password) {
        return true;
    } else return false;
}

QString Server::get_data(QString _password) {
    if (_password == password){
        return data;
    } else return "access denied";
}

QRectF Server::boundingRect() const
{
    return QRectF (-20,-20,40,40);
}

void Server::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::white);
    painter->drawPixmap(-20,-20,40,40, pixmap);
    painter->drawText(boundingRect(), Qt::AlignBottom, QString::number(item_number));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Server::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
       this->setPos(mapToScene(event->pos()));
       emit  sendPos(mapToScene(event->pos()));

    Q_UNUSED(event)
}

void Server::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void Server::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void Server::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    dialog->server_number = this->server_number;
    dialog->exec();

   Q_UNUSED(event)

}


