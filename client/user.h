#ifndef USER_H
#define USER_H


#include "chat.h"
#include <QString>
#include <QList>
#include <QSet>
#include <QMap>

class User
{
private:
    QString login;
    QString password;
    QSet<QString> u_list;
    QMap<QString, Chat> u_chats;
public:
    User() = default;
    ~User() = default;
    void setLogin(QString &);
    void setPassword(QString &);
    void setUsersList(QList<QString> &);
    void setChatsList(QList<QString> &);
    void addChat(QString &, QString &, QString &, QString &, QString &);
    QString & getLogin();
    QString & getPassword();
    QMap<QString, Chat> & getUserContacts();
    QSet<QString> & getUsersList();
};

#endif // USER_H
