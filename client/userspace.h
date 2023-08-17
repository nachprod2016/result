#ifndef USERSPACE_H
#define USERSPACE_H

#include <QDialog>
#include "chat.h"
#include <QMap>
#include <QListWidgetItem>
#include "authentication.h"

namespace Ui {
class UserSpace;
}

class UserSpace : public QDialog
{
    Q_OBJECT

public:
    explicit UserSpace(QWidget *parent = nullptr);
    ~UserSpace();
    void getUsersList(QMap<QString, Chat> *);
    void getChatMessages(QString);
    void showUsers();
    QString & getChatNumber();
    QMap<QString, Chat> * getContacts();
    void getOutPutMessage(QString &, QString &);
    void makeMessageFormat();
    void getSelectContact(QString &);
    void setLogin(QString &);
    void blockListContacts(bool);
    void addNewContact(QString &, QString &);

private slots:
    void on_buttonLogout_clicked();
    void on_listContacts_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_sendMessageButton_clicked();
    void on_addContact_clicked();

public slots:
    void showReceivedMessages();

signals:
    void closeUserSpace();
    void MessagesIsEmpty();
    void createNewMessage();
    void addContact();

private:
    Ui::UserSpace *ui;
    QMap<QString, Chat> * contacts;
    QMap<QString, QString> outPutMessages;
    QListWidgetItem * selectedContact;
    QString login;
    QString chatNumber;
};

#endif // USERSPACE_H
