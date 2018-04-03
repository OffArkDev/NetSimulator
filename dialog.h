#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "mythread.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    int server_number;


private:
    Ui::Dialog *ui;

    QString password;

private slots:
        void on_pushButton_clicked();

        void on_sendDataButton_clicked();

        void on_setPasswordButton_clicked();

        void on_showPasswordButton_clicked();

        void on_addServicesButton_clicked();

        void on_clearPushButton_clicked();

public slots:
        void recieveData(QString str);
        void getDataClient(QString str, QString psw);
        void recievePassword(QString psw);
        void recieveDataPassword(QString psw);
        void getAttacked(QString name, int probability, bool channeled);
        void onValueChanged(int count, QString nameThread);
        void getDDoSData(QString data);

signals:
    void sendData(QString str);
    void acceptPassword(bool login);
    void tryChanneledAttack(QString name, int probability, bool channeled);

};

#endif // DIALOG_H
