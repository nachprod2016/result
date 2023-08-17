#ifndef CHAT_H
#define CHAT_H

#include <QString>
#include <QList>
#include "message.h"

class Chat
{
public:
    Chat() = default;
    ~Chat() = default;
    void addMessage(Message &);
    void setData(QString &, QString &, QString &);
    bool isEmptyMesseges();
    QString & getChatID();
    QList<Message> & getMessages();

private:
    QString user1;
    QString user2;
    QString c_id;
    QList<Message> messages;
};

#endif // CHAT_H
