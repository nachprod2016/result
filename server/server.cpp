#include "server.h"

void Server::getPointers(ConnectDB * connectDB, WinServer * winServer, DataBase * dataBase)
{
    c_db = connectDB;
    w = winServer;
    db = dataBase;
}

void Server::go()
{
    c_db->show();
    connect(c_db, &ConnectDB::checkConnectionDB, this, &Server::connectDB);
    connect(w, &WinServer::start, this, &Server::startServer);
}

void Server::connectDB()
{
    QString nameDB;
    QString login;
    QString password;
    c_db->getInformation(nameDB, login, password);
    bool b = db->connectDB(nameDB, login, password);
    if (b == false)
    {
        c_db->attention();
    }
    else
    {
        c_db->close();
        w->getPtrDatabase(db);
        w->showUsers();
        w->show();
    }
}

 void Server::incomingConnection(qintptr socketDescriptor)
 {
     socket = new QTcpSocket();
     socket->setSocketDescriptor(socketDescriptor);
     connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
 }

 void Server::slotReadyRead()
 {
     Data.clear();
     Data = socket->readAll();
     doc = QJsonDocument::fromJson(Data, &docError);
     runСommand();
 }

 void Server::sendToClient()
 {
     Data.clear();
     QString send = "{" + message + "}";
     message.clear();
     Data.append(send.toUtf8());
     socket->write(Data);
 }

 void Server::addRecord(QString & str)
 {
     if (message.size() == 0)
     {
         message += str;
     }
     else
     {
         message += ',' + str;
     }
     str.clear();
 }

 void Server::runСommand()
 {
     int command = doc.object().value("command").toInt();
     switch (command)
     {
         case 0:
         {
             QString q;
             QString login = doc.object().value("login").toString();
             QString password = doc.object().value("password").toString();
             bool res = db->addUser(login, password);
             if (res == true)
             {
                 q  = "\"command\":0";
                 w->addItem(login);
             }
             else
             {
                 q  = "\"command\":1";
             }
             addRecord(q);
             sendToClient();
             break;
         }
        case 1:
        {
             QString q;
             QString login = doc.object().value("login").toString();
             QString password = doc.object().value("password").toString();
             bool res = db->checkUser(login, password, 'a');
             if (res == false)
             {
                 q  = "\"command\":2";
             }
             else
             {
                 q  = "\"command\":3";
             }
             addRecord(q);
             QString userListJson = "\"usersList\":\"";
             QList<QString> userList;
             db->getUsersList(userList);
             makeString(userListJson, userList);
             addRecord(userListJson);
             QString userChats;
             db->makeChatsForClient(login, userChats);
             addRecord(userChats);
             sendToClient();
             break;
        }
        case 2:
        {
            QString chatID = doc.object().value("chatID").toString();
            QList<QString> authors;
            QList<QString> messages;
            db->getChatMessagesForClient(chatID, authors, messages);
            QString messageBox;
            int sizeMessageBox = 0;
            makeMessageBoxForClient(authors, messages, messageBox, chatID, sizeMessageBox);
            addRecord(messageBox);
            QString size = "\"size\":" + QString::number(sizeMessageBox);
            addRecord(size);
            QString command = "\"command\":4";
            addRecord(command);
            sendToClient();
            break;
        }
        case 3:
        {
            QString chatID = doc.object().value("chatID").toString();
            QString author = doc.object().value("author").toString();
            QString message = doc.object().value("message").toString();
            db->addMessage(chatID, author, message);
            break;
        }
        case 4:
        {
            QString user1 = doc.object().value("user1").toString();
            QString user2 = doc.object().value("user2").toString();
            QString message = doc.object().value("message").toString();
            QString chatID;
            db->addChat(user1, user2, chatID);
            db->addMessage(chatID, user1, message);
            QString buffer = "\"user1\":\"" + user1 + "\"";
            addRecord(buffer);
            buffer = "\"user2\":\"" + user2 + "\"";
            addRecord(buffer);
            buffer = "\"author\":\"" + user1 + "\"";
            addRecord(buffer);
            buffer = "\"message\":\"" + message + "\"";
            addRecord(buffer);
            buffer = "\"chatID\":\"" + chatID + "\"";
            addRecord(buffer);
            buffer = "\"command\":5";
            addRecord(buffer);
            sendToClient();
            break;
        }
     }
 }

 void Server::startServer()
 {
     this->listen(QHostAddress::Any, 5555);
 }

 void Server::makeString(QString & jsonList, QList<QString> & list)
 {
     QList<QString>::iterator begin = list.begin();
     QList<QString>::iterator end = list.end();
     for (begin; begin != end; begin++)
     {
         jsonList += *begin;
         if (begin != end - 1)
         {
             jsonList += '|';
         }
     }
     jsonList += "\"";
 }

 void Server::makeMessageBoxForClient(QList<QString> & authors, QList<QString> & messages, QString & messageBox, QString & chatID, int &size)
 {
     messageBox = "\"messageBox\":[";
     QList<QString>::iterator b_author =  authors.begin();
     QList<QString>::iterator e_author  =  authors.end();
     QList<QString>::iterator b_messages =  messages.begin();
     while (b_author != e_author)
     {
         QString element = "{\"author\":\"" + *b_author + "\",";
         element += "\"chatID\":\"" + chatID + "\",";
         element += "\"message\":\"" + *b_messages + "\"}";
         if (b_author != e_author - 1)
         {
             element += ',';
         }
         messageBox += element;
         b_author++;
         b_messages++;
         size++;
     }
     messageBox += ']';
 }
