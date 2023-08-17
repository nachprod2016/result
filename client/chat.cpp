#include "chat.h"

void Chat::setData(QString & chatNumber, QString & u1, QString & u2)
{
    c_id = chatNumber;
    user1 = u1;
    user2 = u2;
}

void Chat::addMessage(Message & m)
{
    messages.push_back(m);
}

bool Chat::isEmptyMesseges()
{
    if(messages.size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

QString & Chat::getChatID()
{
    return c_id;
}

QList<Message> & Chat::getMessages()
{
    return messages;
}
