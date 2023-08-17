#include "database.h"
#include <QDebug>

bool DataBase::connectDB(QString & nameDB, QString & login, QString & password)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName(nameDB);
    db.setUserName(login);
    db.setPassword(password);
    return db.open();
}

bool DataBase::checkUser(QString & login, QString & password, char key)
{
    QString queryText = "select login, password from users where ";
    queryText += "login = \'" + login + "\'";
    if (key == 'a')
    {
        queryText  += "and password = \'" + password + "\'";
    }
    QSqlQuery query = QSqlQuery(db);
    query.exec(queryText);
    if (query.size() == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool DataBase::addUser(QString & login, QString & password)
{
    if (checkUser(login, password, 'r') == false)
    {
        QString queryText = "insert into users (u_id, login, password) values(default, ";
        queryText += '\'' + login + "\', " + '\'' + password + "\')";
        QSqlQuery query = QSqlQuery(db);
        query.exec(queryText);
        return true;
    }
    else
    {
        return false;
    }
}

void DataBase::getUsersList(QList<QString> & list)
{
    QString queryText = "select login from users";
    QSqlQuery query;
    query.exec(queryText);
    query.first();
    for (int i = 0; i < query.size(); i++)
    {
        list.push_back(query.value(0).toString());
        query.next();
    }
}

void DataBase::getChatMessages(QString & chatName, QList<QString> & list)
{
    QString queryText = "select author, message from messages where c_id = ";
    queryText += '\'' + chatName + '\'';
    QSqlQuery query;
    query.exec(queryText);
    query.first();
    int size = query.size();
    for (int i = 0; i < size; i++)
    {
        QString str = query.value("author").toString() + " : ";
        str += query.value("message").toString();
        list.push_back(str);
        query.next();
    }
    list.push_back("----------------------------------------------------------------------------------------------------------------");
}

void DataBase::getUserChats(QString & login, QList<QString> & chatList)
{
    QString queryText = "select * from chats where user1 = ";
    queryText += '\'' + login + "\' or user2 = \'" + login +'\'';
    QSqlQuery query;
    query.exec(queryText);
    query.first();
    for (int i = 0; i < query.size(); i++)
    {
        chatList.push_back(query.value(0).toString());
        query.next();
    }
}

void DataBase::makeChatsForClient(QString & login, QString & jsonChats)
{
    QString queryText = "select * from chats where user1 = ";
    queryText += '\'' + login + "\' or user2 = \'" + login +'\'';
    QSqlQuery query;
    query.exec(queryText);
    query.first();
    jsonChats += "\"userChats\":\"";
    for (int i = 0; i < query.size(); i++)
    {
        jsonChats += query.value(0).toString() + "#$%";
        jsonChats += query.value(1).toString() + "#$%";
        jsonChats += query.value(2).toString();
        if (i != query.size() - 1)
        {
            jsonChats += '|';
        }
        query.next();
    }
    jsonChats += "\"";
}

void DataBase::getChatMessagesForClient(QString & chatID, QList<QString> & authors, QList<QString> & messages)
{
    QString queryText = "select author, message from messages where c_id = ";
    queryText += '\'' + chatID + '\'';
    QSqlQuery query;
    query.exec(queryText);
    query.first();
    for (int i = 0; i < query.size(); i++)
    {
        authors.push_back(query.value(0).toString());
        messages.push_back(query.value(1).toString());
        query.next();
    }
}

void DataBase::addMessage(QString & chatID, QString & author, QString & message)
{
    QString queryText  = "insert into messages (m_id, c_id, author, message) values(default, ";
    queryText += '\'' + chatID + "\', " + '\'' + author + "\', " + '\'' + message + "\')";
    QSqlQuery query;
    query.exec(queryText);
}

void DataBase::addChat(QString & user1, QString & user2, QString & c_id)
{
    QString queryText = "insert into chats (c_id, user1, user2) values(default, ";
    queryText += '\'' + user1 + "\', " + '\'' + user2 + "\')";
    QSqlQuery query;
    query.exec(queryText);
    queryText.clear();
    queryText = "select c_id from chats where user1 = ";
    queryText += '\'' + user1 + "\' and user2 = \'" + user2 + '\'';
    query.exec(queryText);
    query.first();
    c_id = query.value(0).toString();
}
