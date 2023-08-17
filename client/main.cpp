#include <QApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client client;
    Authentication A;
    GetUserData G;
    client.start(&A, &G);
    return a.exec();
}
