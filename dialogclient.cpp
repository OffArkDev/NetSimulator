#include "dialogclient.h"
#include "ui_dialogclient.h"
#include <QFile>

DialogClient::DialogClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogClient)
{
    ui->setupUi(this);
    ui->attacksComboBox->addItem("bruteforce");
    ui->attacksComboBox->addItem("DDoS");
    ui->attacksComboBox->addItem("Attack 80 port");
    ui->attacksComboBox->addItem("Windows vulnerability");
    ui->attacksComboBox->addItem("Linux vulnerability");
    ui->attacksComboBox->addItem("");

    ui->attacksTableWidget->setRowCount(1);
    ui->attacksTableWidget->setColumnCount(6);


    ui->attacksTableWidget->setColumnWidth(0, 63);
    ui->attacksTableWidget->setColumnWidth(1, 35);
    ui->attacksTableWidget->setColumnWidth(2, 35);
    ui->attacksTableWidget->setColumnWidth(3, 23);
    ui->attacksTableWidget->setColumnWidth(4, 23);
    ui->attacksTableWidget->setColumnWidth(5, 25);

    ui->attacksTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("attacks"));
    ui->attacksTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("time"));
    ui->attacksTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("prob"));
    ui->attacksTableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("cN"));
    ui->attacksTableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("isC"));
    ui->attacksTableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("s"));
}

DialogClient::~DialogClient()
{
    delete ui;
}

void DialogClient::on_pushButton_clicked()
{

}

void DialogClient::on_sendDataBUtton_clicked()
{
    data = ui->sendDataLineEdit->text();
    //channel->data = data;
    emit sendData(data, ui->loginLineEdit->text());
}

void DialogClient::recieveData(QString str) {
    ui->getDataTextEdit->setText(str);
}

void DialogClient::recieveResultLogin(bool rsl) {
    if (rsl) {
        ui->getDataTextEdit->setText("login successeful");
    } else  ui->getDataTextEdit->setText("login failed ");
}

void DialogClient::on_loginButton_clicked()
{
    emit tryPassword(ui->loginLineEdit->text());
}

void DialogClient::on_getDataButton_clicked()
{
    emit getData(ui->loginLineEdit->text());
}

void DialogClient::on_addAttackButton_clicked()
{
    QString aName;
    if ( ui->attacksComboBox->currentText() == "")
    aName = ui->attacksLineEdit->text();
    else aName = ui->attacksComboBox->currentText();
    QString aTime = ui->attacksTimeEdit->text();
    QString aProb = ui->probabilitySpinBox->text();
    QString cN = ui->channelSpinBox->text();
    QString isC = "-";
    if (ui->channeledCheckBox->isChecked())
        isC = "+";
    QString aS = "-";
    if (ui->simulationCheckBox->isChecked())
        aS = "+";


       ui->attacksTableWidget->setItem(attackRow,0, new QTableWidgetItem(aName));
       ui->attacksTableWidget->setItem(attackRow,1, new QTableWidgetItem(aTime));
       ui->attacksTableWidget->setItem(attackRow,2, new QTableWidgetItem(aProb));
       ui->attacksTableWidget->setItem(attackRow,3, new QTableWidgetItem(cN));
       ui->attacksTableWidget->setItem(attackRow,4, new QTableWidgetItem(isC));
       ui->attacksTableWidget->setItem(attackRow,5, new QTableWidgetItem(aS));

       attackRow++;
       ui->attacksTableWidget->insertRow(attackRow);
}

void DialogClient::on_attackButton_clicked()
{

    bool isC;
    bool isS;
    for (int i = 0; i < attackRow; i++) {
        isC = false;
        if (ui->attacksTableWidget->item(i,4)->text() == "+")
            isC = true;
        isS = false;
        if (ui->attacksTableWidget->item(i, 5)->text() == "+") {
            if (ui->attacksTableWidget->item(i,0)->text() == "bruteforce")
                bruteForceAttack();
            if (ui->attacksTableWidget->item(i,0)->text() == "DDoS")
                ddosAttack();
        } else emit tryAttack(ui->attacksTableWidget->item(i,0)->text(), ui->attacksTableWidget->item(i,2)->text().toInt(), isC);
    }


}

void DialogClient::bruteForceAttack() {

        QString password;
        ui->getDataTextEdit->setText("");

        QFile inputFile("D:/projects/QT/Simulator/dictionary.txt");
        if (inputFile.open(QIODevice::ReadOnly))
        {
           QTextStream in(&inputFile);
           bool found = false;
           while (!in.atEnd())
           {
              QString line = in.readLine();
              emit tryPassword(line);
              if (ui->getDataTextEdit->toPlainText() == "login successeful") {
                  found = true;
                  password = line;
                  break;
              }


           }
           inputFile.close();

           if (found) {
               ui->getDataTextEdit->setText("simple bruteforce success, password is " + password);
           } else ui->getDataTextEdit->setText("bruteforce failed");


        } else ui->getDataTextEdit->append("file not open");

}

void DialogClient::ddosAttack() {
    ui->getDataTextEdit->setText("DDoS is working...u can check the server window");
    int q = qrand()%10;
    emit sendDDoSData(QString::number(q));
}
