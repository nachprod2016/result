#include "connectdb.h"
#include "ui_connectdb.h"

ConnectDB::ConnectDB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDB)
{
    ui->setupUi(this);
}

ConnectDB::~ConnectDB()
{
    delete ui;
}

void ConnectDB::on_cancel_clicked()
{
    close();
}


void ConnectDB::on_ok_clicked()
{
    nameDB = ui->lineDB->text();
    login = ui->LineLog->text();
    password = ui->LinePass->text();
    emit checkConnectionDB();
}

void ConnectDB::attention()
{
    QMessageBox::about(this, "Внимание", "Соединение с базой данных не было установлено!");
}

void ConnectDB::getInformation(QString & nDB, QString & log, QString & pass)
{
    nDB = nameDB;
    log = login;
    pass = password;
}
