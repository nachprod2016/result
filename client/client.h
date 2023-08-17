#ifndef CLIENT_H
#define CLIENT_H

#include <QDataStream>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QList>
#include "authentication.h"
#include "getuserdata.h"
#include "userspace.h"
#include "user.h"
#include "addcontact.h"

class Client : public QObject
{
    Q_OBJECT

public:
    Client();
    ~Client();
    void start(Authentication *, GetUserData *);
    void callUserDataForm(char);
    void addRecord(QString &);
    void sendToServer();
    void runСommand();
    void clearData();

public slots:
    void clickedRegistration();
    void clickedAuthorization();
    void readyRead();
    void sendUserData();
    void cancelClicked();
    void openUserSpace();
    void closeUserSpace();
    void getMessagesForChat();
    void getMessageBoxFromServer();
    void getNewMessage();
    void addContact();
    void addNewContact();

signals:
    void getMessages();

private:
    QTcpSocket *socket;
    Authentication * authentication;
    GetUserData * getUserData;
    UserSpace * userSpace;
    AddContact * add;
    QString message;
    QByteArray Data;
    QJsonDocument doc;
    QJsonParseError docError;
    User * user;
};

#endif // CLIENT_H
