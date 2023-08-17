#include "userspace.h"
#include "ui_userspace.h"
#include <QDebug>

UserSpace::UserSpace(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserSpace)
{
    ui->setupUi(this);
    ui->sendMessageButton->setDisabled(true);
}

UserSpace::~UserSpace()
{
    delete ui;
}

void UserSpace::getUsersList(QMap<QString, Chat> * list)
{
    contacts = list;
}

void UserSpace::showUsers()
{
    if (contacts->size() != 0)
    {
        QMap<QString, Chat>::iterator begin = contacts->begin();
        QMap<QString, Chat>::iterator end = contacts->end();
        ui->listContacts->clear();
        for (; begin != end; begin++)
        {
            ui->listContacts->addItem(begin.key());
        }
    }
}

void UserSpace::on_buttonLogout_clicked()
{
    emit closeUserSpace();
}


void UserSpace::on_listContacts_currentItemChanged(QListWidgetItem *current, QListWidgetItem *)
{
    selectedContact = current;
    ui->sendMessageButton->setDisabled(false);
    QString contact = current->text();
    Chat chatWithContact = contacts->find(contact).value();
    if (chatWithContact.isEmptyMesseges() == true)
    {
        chatNumber = chatWithContact.getChatID();
        emit MessagesIsEmpty();
        blockListContacts(true);
    }
    else
    {
        QString outPutMessage;
        QString key = current->text();
        getOutPutMessage(key, outPutMessage);
        ui->chatBrowser->setText(outPutMessage);
    }
}

QString & UserSpace::getChatNumber()
{
    return chatNumber;
}

QMap<QString, Chat> * UserSpace::getContacts()
{
    return contacts;
}


void UserSpace::getOutPutMessage(QString & key, QString & outPutMessage)
{
    outPutMessage = outPutMessages.find(key).value();
}

void UserSpace::showReceivedMessages()
{
    makeMessageFormat();
    QString key = selectedContact->text();
    QString outPutMessage;
    getOutPutMessage(key, outPutMessage);
    ui->chatBrowser->setText(outPutMessage);
    blockListContacts(false);
}

void UserSpace::makeMessageFormat()
{
    QString outPutMessage;
    QString key = selectedContact->text();
    Chat chat = contacts->find(key).value();
    QList<Message> messages = contacts->find(key).value().getMessages();
    QList<Message>::iterator begin = messages.begin();
    QList<Message>::iterator end = messages.end();
    while (begin != end)
    {
        QString author;
        QString message;
        begin->getAuthor(author);
        begin->getMessage(message);
        outPutMessage.push_back(author + " : " + message + '\n');
        begin++;
    }
    outPutMessages.insert(key, outPutMessage);
}

void UserSpace::getSelectContact(QString & contact)
{
    contact = selectedContact->text();
}

void UserSpace::setLogin(QString & log)
{
    login = log;
}

void UserSpace::on_sendMessageButton_clicked()
{
    if (ui->inMessage->text().size() != 0)
    {
        QString inputMessage =  ui->inMessage->text();
        QString key = selectedContact->text();
        outPutMessages.find(key).value().push_back(login + " : " + inputMessage + '\n');
        ui->chatBrowser->setText(outPutMessages.find(selectedContact->text()).value());
        ui->inMessage->clear();
        QString chatId = contacts->find(key).value().getChatID();
        Message msg(login, inputMessage, chatId);
        contacts->find(key).value().addMessage(msg);
        emit createNewMessage();
    }
}

void UserSpace::on_addContact_clicked()
{
    emit addContact();
}

void UserSpace::blockListContacts(bool b)
{
    ui->listContacts->setDisabled(b);
}

void UserSpace::addNewContact(QString & newContact, QString & Msg)
{
    ui->listContacts->addItem(newContact);
    outPutMessages.insert(newContact, Msg + '\n');
}
