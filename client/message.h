#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

class Message
{
private:
    QString author;
    QString message;
    QString c_id;

public:
    Message() = delete;
    Message(QString &, QString &&, QString &);
    Message(QString &, QString &, QString &);
    ~Message() = default;
    void getAuthor(QString &);
    void getMessage(QString &);
    void getChatID(QString &);
};

#endif // MESSAGE_H
