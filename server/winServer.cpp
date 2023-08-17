#include "winServer.h"
#include "ui_winServer.h"

WinServer::WinServer  (QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WinServer)
{
    ui->setupUi(this);
}

WinServer::~WinServer ()
{
    delete ui;
}

void WinServer::on_startServer_clicked()
{
    emit start();
    ui->startServer->setDisabled(true);
}

void WinServer::showUsers()
{
    QList<QString> list;
    db->getUsersList(list);
    QList<QString>::iterator begin = list.begin();
    QList<QString>::iterator end = list.end();
    ui->listUsers->clear();
    for (begin; begin != end; begin++)
    {
        ui->listUsers->addItem(*begin);
    }
}

void WinServer::on_listUsers_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->UsersMess->clear();
    QList<QString> listChats;
    QList<QString> listMessages;
    QString login = current->text();
    db->getUserChats(login, listChats);
    QList<QString>::iterator begin = listChats.begin();
    QList<QString>::iterator end = listChats.end();
    QString out;
    for (begin; begin != end; begin++)
    {
        db->getChatMessages(*begin, listMessages);
    }
    begin = listMessages.begin();
    end = listMessages.end();
    for (begin; begin != end; begin++)
    {
        out += *begin + '\n';
    }
    ui->UsersMess->setText(out);
}

void WinServer::addItem(QString & login)
{
    ui->listUsers->addItem(login);
}

void WinServer::getPtrDatabase(DataBase * DataBase)
{
    db = DataBase;
}
