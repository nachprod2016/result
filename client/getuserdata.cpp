#include "getuserdata.h"
#include "ui_getuserdata.h"
#include <QMessageBox>
#include <QDebug>

GetUserData::GetUserData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetUserData)
{
    ui->setupUi(this);
}

GetUserData::~GetUserData()
{
    delete ui;
}

void GetUserData::on_Ok_clicked()
{
    login = ui->login_line->text();
    password = ui->password_line->text();
    if (login.length() == 0 || password.length() == 0)
    {
        QMessageBox::about(this, "Внимание", "Введены не все пользовательские данные");
    }
    else
    {
        emit sendUserData();
    }
}

void GetUserData::on_cancel_clicked()
{
    emit cancelClicked();
}

void GetUserData::getUserData(QString & log, QString & pass, char & c)
{
    log = login;
    pass = password;
    c = type;
}

void GetUserData::setType(char t)
{
    type = t;
}

void GetUserData::clearForm()
{
    ui->login_line->clear();
    ui->password_line->clear();
}
