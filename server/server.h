#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include "winServer.h"
#include "connectdb.h"
#include "database.h"

class Server : public QTcpServer
{

    Q_OBJECT

public:
    Server() = default;
    ~Server() = default;
    void getPointers(ConnectDB *, WinServer *, DataBase *);
    void go();
    void sendToClient();
    void addRecord(QString & str);
    void runСommand();
    void makeString(QString &, QList<QString> &);
    void makeMessageBoxForClient(QList<QString> &, QList<QString> &, QString &, QString &, int &);

private:
    ConnectDB *c_db;
    WinServer *w;
    DataBase *db;
    QTcpSocket *socket;
    QByteArray Data;
    QJsonDocument doc;
    QJsonParseError docError;
    QString message;
    void startServer();

public slots:
    void connectDB();
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
};

#endif // SERVER_H
