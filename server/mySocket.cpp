#include "mySocket.h"
#include <QDebug>

/*bool MySocket::startServer()
{
    return this->listen(QHostAddress::Any, 5555);
}

void MySocket::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
   // connect(socket, &QTcpSocket::readyRead, this, &MySocket::slotReadyRead);
    //connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    sockets.push_back(socket);
}

void MySocket::slotReadyRead()
{
    Data.clear();
    Data = socket->readAll();
    doc = QJsonDocument::fromJson(Data, &docError);
    runСommand();
}

void MySocket::sendToClient()
{
    Data.clear();
    QString send = "{" + message + "}";
    message.clear();
    Data.append(send.toUtf8());
    socket->write(Data);
}

bool MySocket::connectDB(QString & nameDB, QString & login, QString & password)
{
    bool a = db.connectDB(nameDB, login, password);
    if (a == true)
    {
        db.settingDB();
    }
    return a;
}

void MySocket::getUserList(QList<QString> & list)
{
    db.getUsersList(list);
}


void MySocket::getUserMessages(QString & login, QList<QString> & list)
{
    QList<QString> userChats;
    db.getUserChats(login, userChats);
    QList<QString>::iterator begin = userChats.begin();
    QList<QString>::iterator end = userChats.end();
    for (begin; begin != end; begin++)
    {
        db.getChatMessages(*begin, list);
    }
}

void MySocket::runСommand()
{
    int command = doc.object().value("command").toInt();
    switch (command)
    {
        case 0:
        {
        /*
            QString login = doc.object().value("login").toString();
            QString password = doc.object().value("password").toString();
            bool res = db.checkUser(login, password, 'r');
            if (res == false)
            {

            }
            */
            /*QString q  = "\"command\":1";
            addRecord(q);
            sendToClient();
            break;
        }
    }
}*/

/*void MySocket::addRecord(QString & str)
{
    if (message.size() == 0)
    {
        message += str;
    }
    else
    {
        message += ',' + str;
    }
}
*/
