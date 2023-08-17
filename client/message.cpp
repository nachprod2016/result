#include "message.h"

Message::Message(QString & author, QString && message, QString & c_id) : author(author), message(message), c_id(c_id){}

Message::Message(QString & author, QString & message, QString & c_id) : author(author), message(message), c_id(c_id){}

void Message::getAuthor(QString & A)
{
    A = author;
}

void Message::getMessage(QString & M)
{
    M = message;
}

void Message::getChatID(QString & chatID)
{
    chatID = c_id;
}
