#include "user.h"
#include <QDebug>

void User::setLogin(QString & log)
{
    login = log;
}

void User::setPassword(QString & pass)
{
    password = pass;
}

void User::setUsersList(QList<QString> & list)
{
    QList<QString>::iterator end = list.end();
    QList<QString>::iterator begin = list.begin();
    for (; begin != end; begin++)
    {
        u_list.insert(*begin);
    }
}

void User::setChatsList(QList<QString> & list)
{
    QList<QString>::iterator begin = list.begin();
    QList<QString>::iterator end = list.end();
    for (; begin != end; begin++)
    {
        QString buf = *begin;
        QList<QString> bufList = buf.split("#$%");
        QList<QString>::iterator b = bufList.begin();
        QString c_id = *b;
        b++;
        QString user1 = *b;
        b++;
        QString user2 = *b;
        Chat chat;
        chat.setData(c_id, user1, user2);
        QString key;
        if (user1 == login)
        {
            key = user2;
        }
        else
        {
            key = user1;
        }
        u_chats.insert(key, chat);
    }
}

QString & User::getLogin()
{
    return login;
}

QString & User::getPassword()
{
    return password;
}


QMap<QString, Chat> & User::getUserContacts()
{
    return u_chats;
}

QSet<QString> & User::getUsersList()
{
    return u_list;
}

void User::addChat(QString & chatID, QString & user1, QString & user2, QString & author, QString & message)
{
    Message m(author, message, chatID);
    Chat chat;
    chat.setData(chatID, user1, user2);
    chat.addMessage(m);
    u_chats.insert(user2, chat);
}
