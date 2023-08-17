#include "addcontact.h"
#include "ui_addcontact.h"

AddContact::AddContact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addContact)
{
    ui->setupUi(this);
}

AddContact::~AddContact()
{
    delete ui;
}

void AddContact::setUsersList(QSet<QString> & newUsers, QMap<QString, Chat> & contacts, QString & login)
{
    bool f = true;
    ui->add->setDisabled(f);
    QSet<QString> ::iterator begin = newUsers.begin();
    QSet<QString> ::iterator end = newUsers.end();
    while (begin != end)
    {
        if (contacts.find(*begin) == contacts.end() && *begin != login)
        {
            f = false;
            ui->listUsers->addItem(*begin);
        }
        begin++;
    }
    ui->add->setDisabled(f);
}

void AddContact::on_add_clicked()
{
    emit addNewContact();
    hide();
}

void AddContact::on_listUsers_currentItemChanged(QListWidgetItem *current, QListWidgetItem *)
{
    selectContact = current;
}

void AddContact::getSelectContact(QString & contact)
{
    contact = selectContact->text();
}
