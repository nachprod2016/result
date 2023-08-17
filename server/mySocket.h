#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include "database.h"

class MySocket : public QTcpServer
{
    Q_OBJECT

public:
    MySocket() = default;
    ~MySocket() = default;
    /*bool startServer();
    QTcpSocket *socket;
    void sendToClient();
    bool connectDB(QString &, QString &, QString &);
    void getUserList(QList<QString> &);
    void getUserMessages(QString &, QList<QString> &);
    void runСommand();
    void addRecord(QString &);*/

private:
    /*QString message;
    QVector<QTcpSocket*> sockets;
    QByteArray Data;
    QJsonDocument doc;
    QJsonParseError docError;
    DataBase db;*/

public slots:
    /*void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();*/
};

#endif // MYSOCKET_H
