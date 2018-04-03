#include "dialog.h"
#include "ui_dialog.h"
#include "server.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->servicesComboBox->addItem("password");
    ui->servicesComboBox->addItem("Windows XP");
    ui->servicesComboBox->addItem("Linux");
    ui->servicesComboBox->addItem("Windows 7");

}


Dialog::~Dialog()
{
    delete ui;
}




void Dialog::on_pushButton_clicked()
{
    ui->serverNumberLabel->setText(QString::number(this->server_number));
}


void Dialog::on_sendDataButton_clicked()
{
  emit sendData(ui->dataTextEdit->toPlainText());
}

void Dialog::recieveData(QString str){
    ui->dataTextEdit->setText(str);
}

void Dialog::recievePassword(QString psw) {
    if (psw == password) {
        emit acceptPassword(true);
    } else emit acceptPassword(false);
}

void Dialog::on_setPasswordButton_clicked()
{
    password = ui->passwordLineEdit->text();
}

void Dialog::on_showPasswordButton_clicked()
{
    ui->passwordLineEdit->setText(password);
}

void Dialog::recieveDataPassword(QString psw) {
    if (psw == password) {
        emit sendData(ui->dataTextEdit->toPlainText());
    }
}

void Dialog::getDataClient(QString str, QString psw)
{
    if (psw == password) {
        ui->dataTextEdit->setText(str);
    } else ui->dataTextEdit->setText("false");
}

void Dialog::on_addServicesButton_clicked()
{
   ui->servicesTextEdit->append(ui->servicesComboBox->currentText());
}

void Dialog::getAttacked(QString name, int probability, bool channeled)
{

    int q = qrand()%100;
    if (q<probability) {
        ui->sucAttackstextEdit->append(name);
    }

    if (channeled) {
        emit tryChanneledAttack(name, probability, true);
    }

}
void Dialog::getDDoSData(QString data) {
    int countThreads = 10;
    MyThread *myThread = new MyThread[countThreads];
    ui->dataTextEdit->setText("work1 " + data);
    for (int i = 0; i < countThreads; i++)
    connect(&myThread[i], SIGNAL(valueChanged(int, QString)), this, SLOT(onValueChanged(int, QString)));
    for (int i = 0; i < countThreads; i++) {
    myThread[i].name = "Thread number is " + QString::number(i);
        myThread[i].start();
        }
}

void Dialog::onValueChanged(int count, QString nameThread)
{
    ui->dataTextEdit->append(nameThread + " ");
    ui->dataTextEdit->append(QString::number(count));
}

void Dialog::on_clearPushButton_clicked()
{
    ui->sucAttackstextEdit->clear();
}
