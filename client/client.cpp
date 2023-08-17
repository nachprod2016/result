#include "client.h"

Client::Client()
{
    socket = new QTcpSocket(this);
}

Client::~Client()
{
    delete socket;
}

void Client::start(Authentication * A, GetUserData * G)
{
    authentication = A;
    getUserData = G;
    connect(socket, &QTcpSocket::readyRead, this, &Client::readyRead);
    connect(getUserData, &GetUserData::sendUserData, this, &Client::sendUserData);
    connect(getUserData, &GetUserData::cancelClicked, this, &Client::cancelClicked);
    connect(authentication, &Authentication::registrationClicked, this, &Client::clickedRegistration);
    connect(authentication, &Authentication::authorizationClicked, this, &Client::clickedAuthorization);
    connect(authentication, &Authentication::openUserSpaceClicked, this, &Client::openUserSpace);
    authentication->show();
}

void Client::clickedRegistration()
{
    char r = 'r';
    callUserDataForm(r);
}

void Client::clickedAuthorization()
{
    char a = 'a';
    callUserDataForm(a);
}

void Client::callUserDataForm(char c)
{
    bool flag = socket->waitForConnected();
    if (flag == false)
    {
        socket->connectToHost("127.0.0.1", 5555);
    }
    flag = socket->waitForConnected();
    if (flag == false)
    {
        authentication->sleepServer();
        return;
    }
    else
    {
        authentication->hide();
        getUserData->setType(c);
        getUserData->show();
        getUserData->clearForm();
    }
}

void Client::sendUserData()
{
    char type;
    QString buffer;
    QString log;
    QString pass;
    getUserData->getUserData(log, pass, type);
    buffer = "\"login\":\"" + log + "\"";
    addRecord(buffer);
    buffer = "\"password\":\"" + pass + "\"";
    addRecord(buffer);
    if (type == 'r')
    {
        buffer = "\"command\":0";
    }
    else if (type == 'a')
    {
        buffer = "\"command\":1";
    }
    addRecord(buffer);
    authentication->show();
    getUserData->hide();
    sendToServer();
}

void Client::addRecord(QString & str)
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

void Client::sendToServer()
{
    Data.clear();
    QString send = "{" + message + "}";
    message.clear();
    Data.append(send.toUtf8());
    socket->write(Data);
}
void Client::cancelClicked()
{
    getUserData->hide();
    authentication->show();
}

void Client::readyRead()
{
    Data.clear();
    Data = socket->readAll();
    doc = QJsonDocument::fromJson(Data, &docError);
    runСommand();
}

void Client::runСommand()
{
    int command = doc.object().value("command").toInt();
    switch (command)
    {
        case 0:
        {
            QMessageBox::about(authentication, "Внимание", "Регистрация прошла успешно!");
            break;
        }
        case 1:
        {
            QMessageBox::about(authentication, "Внимание", "Пользователь с таким логином уже зарегестрирован!");
            break;
        }
        case 2:
        {
            QMessageBox::about(authentication, "Внимание", "Неверный логин или пароль!");
            break;
        }
        case 3:
        {
            QString buffer = doc.object().value("usersList").toString();
            QList<QString> bufferList = buffer.split('|');
            user = new User();
            userSpace = new UserSpace();
            connect(userSpace, &UserSpace::closeUserSpace, this, &Client::closeUserSpace);
            connect(userSpace, &UserSpace::MessagesIsEmpty, this, &Client::getMessagesForChat);
            connect(this, &Client::getMessages, userSpace, &UserSpace::showReceivedMessages);
            connect(userSpace, &UserSpace::createNewMessage, this, &Client::getNewMessage);
            connect(userSpace, &UserSpace::addContact, this, &Client::addContact);
            QString login;
            QString password;
            char c;
            getUserData->getUserData(login, password, c);
            user->setLogin(login);
            user->setPassword(password);
            user->setUsersList(bufferList);
            buffer.clear();
            bufferList.clear();
            buffer = doc.object().value("userChats").toString();
            if (buffer.size() != 0)
            {
                bufferList = buffer.split('|');
                user->setChatsList(bufferList);
            }
            userSpace->getUsersList(&(user->getUserContacts()));
            userSpace->setLogin(user->getLogin());
            userSpace->showUsers();
            authentication->openUserSpace(false);
            authentication->authorizationDisable(true);
            authentication->registrationDisable(true);
            break;
        }
        case 4:
        {
            getMessageBoxFromServer();
            break;
        }
        case 5:
        {
            QString user1 = doc.object().value("user1").toString();
            QString user2 = doc.object().value("user2").toString();
            QString chatID = doc.object().value("chatID").toString();
            QString author = doc.object().value("author").toString();
            QString msg = doc.object().value("message").toString();
            user->addChat(chatID, user1, user2, author, msg);
            userSpace->addNewContact(user2, msg);
            userSpace->blockListContacts(false);
            break;
        }
    }
}

void Client::openUserSpace()
{
    authentication->hide();
    userSpace->setWindowTitle(user->getLogin());
    userSpace->show();
}

void Client::closeUserSpace()
{
    userSpace->hide();
    authentication->openUserSpace(true);
    authentication->show();
    delete user;
    delete userSpace;
    delete add;
    user = nullptr;
    userSpace = nullptr;
    add = nullptr;
    authentication->authorizationDisable(false);
    authentication->registrationDisable(false);
}

void Client::getMessagesForChat()
{
    QString chatID = userSpace->getChatNumber();
    QString buffer = "\"command\":2";
    addRecord(buffer);
    buffer = "\"chatID\":\"" + chatID + "\"";
    addRecord(buffer);
    sendToServer();
}

void Client::getMessageBoxFromServer()
{
    QMap<QString, Chat> * chats = userSpace->getContacts();
    QString key;
    userSpace->getSelectContact(key);
    int size = doc.object().value("size").toInt();
    for(int i = 0; i < size; i++)
    {
        QString author = doc.object().value("messageBox")[i]["author"].toString();
        QString message = doc.object().value("messageBox")[i]["message"].toString();
        QString chatID =  doc.object().value("messageBox")[i]["chatID"].toString();
        Message msg(author, message, chatID);
        chats->find(key).value().addMessage(msg);
    }
    emit getMessages();
}

void Client::getNewMessage()
{
    QString key;
    userSpace->getSelectContact(key);
    QList<Message>::iterator ptr = user->getUserContacts().find(key).value().getMessages().end();
    ptr--;
    QString buffer;
    ptr->getAuthor(buffer);
    QString author = "\"author\":\"" + buffer + "\"";
    addRecord(author);
    ptr->getMessage(buffer);
    QString message = "\"message\":\"" + buffer + "\"";
    addRecord(message);
    ptr->getChatID(buffer);
    QString chatID = "\"chatID\":\"" + buffer + "\"";
    addRecord(chatID);
    buffer = "\"command\":3";
    addRecord(buffer);
    sendToServer();
}

void Client::addContact()
{
    add = new AddContact();
    connect(add, &AddContact::addNewContact, this, &Client::addNewContact);
    add->setWindowTitle("Добавить новый контакт");
    add->setModal(true);
    QSet<QString> & list = user->getUsersList();
    QMap<QString, Chat> & contacts = user->getUserContacts();
    QString login = user->getLogin();
    add->setUsersList(list, contacts, login);
    add->show();
}

void Client::addNewContact()
{
    userSpace->blockListContacts(true);
    QString user1 = user->getLogin();
    QString user2;
    add->getSelectContact(user2);
    QString buffer = "\"command\":4";
    addRecord(buffer);
    buffer = "\"user1\":\"" + user1 + "\"";
    addRecord(buffer);
    buffer = "\"user2\":\"" + user2 + "\"";
    addRecord(buffer);
    buffer = "\"message\":\"Привет!\"";
    addRecord(buffer);
    sendToServer();
}
