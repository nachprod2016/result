#ifndef WINSERVER_H
#define WINSERVER_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QLabel>
#include <QMessageBox>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WinServer; }
QT_END_NAMESPACE

class WinServer : public QMainWindow
{
    Q_OBJECT

public:
    WinServer (QWidget *parent = nullptr);
    ~WinServer ();
    void showUsers();
    void addItem(QString &);
    void getPtrDatabase(DataBase *);

signals:
    void start();

public slots:
    void on_startServer_clicked();
    void on_listUsers_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::WinServer *ui;
    DataBase *db;
};
#endif // WINSERVER_H
