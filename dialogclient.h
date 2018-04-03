#ifndef DIALOGCLIENT_H
#define DIALOGCLIENT_H

#include <QDialog>
#include "channel.h"

namespace Ui {
class DialogClient;
}

class DialogClient : public QDialog
{
    Q_OBJECT

public:
    explicit DialogClient(QWidget *parent = 0);
    ~DialogClient();

    int client_number;
    int attackRow = 0;

    QString data;
    QString attack;
    Channel *channel;

    //void setChannel(Channel &ch);

private slots:
    void on_pushButton_clicked();

    void on_sendDataBUtton_clicked();


    void on_loginButton_clicked();

    void on_getDataButton_clicked();

    void on_addAttackButton_clicked();

    void on_attackButton_clicked();

    void bruteForceAttack();
    void ddosAttack();

private:
    Ui::DialogClient *ui;

public slots:
    void recieveData(QString str);
    void recieveResultLogin(bool rsl);

signals:
    void sendData(QString str, QString psw);
    void tryPassword(QString psw);
    void getData(QString psw);
    void tryAttack(QString name, int probability, bool channeled);
    void sendDDoSData(QString data);

};

#endif // DIALOGCLIENT_H
