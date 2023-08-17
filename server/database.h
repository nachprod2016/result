#ifndef DATABASE_H
#define DATABASE_H

#include <QSql>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlRecord>
#include <QList>



class DataBase
{
private:
    QSqlDatabase db;

public:
    DataBase() = default;
    ~DataBase() = default;
    bool connectDB(QString &, QString &, QString &);
    bool checkUser(QString &, QString &, char);
    bool addUser(QString &, QString &);
    void getUsersList(QList<QString> &);
    void getUserChats(QString &, QList<QString> &);
    void makeChatsForClient(QString &, QString &);
    void getChatMessages(QString &, QList<QString> &);
    void getChatMessagesForClient(QString &, QList<QString> &, QList<QString> &);
    void addMessage(QString &, QString &, QString &);
    void addChat(QString &, QString &, QString &);
};

#endif // DATABASE_H
