#include "authentication.h"
#include "ui_authentication.h"
#include "getuserdata.h"
#include "userspace.h"
#include <QDebug>

Authentication::Authentication(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Authentication)
{
    ui->setupUi(this);
    ui->openUserSpacse->setDisabled(true);
    this->show();
}

Authentication::~Authentication()
{
    delete ui;

}

void Authentication::on_registration_clicked()
{
    emit registrationClicked();
}

void Authentication::sleepServer()
{
    QMessageBox::about(this, "Внимание", "Сервер не отвечает");
}


void Authentication::on_authorization_clicked()
{
    emit authorizationClicked();
}

void Authentication::openUserSpace(bool f)
{
    ui->openUserSpacse->setDisabled(f);
}

void Authentication::registrationDisable(bool f)
{
    ui->registration->setDisabled(f);
}

void Authentication::on_openUserSpacse_clicked()
{
     emit openUserSpaceClicked();
}

void Authentication::authorizationDisable(bool f)
{
    ui->authorization->setDisabled(f);
}
