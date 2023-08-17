#include "winServer.h"
#include "server.h"
#include "connectdb.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WinServer w;
    DataBase db;
    ConnectDB c_db;
    Server s;
    s.getPointers(&c_db, &w, &db);
    s.go();
    return a.exec();
}
