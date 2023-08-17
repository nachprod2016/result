#ifndef CONNECTDB_H
#define CONNECTDB_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class ConnectDB;
}

class ConnectDB : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDB(QWidget *parent = nullptr);
    ~ConnectDB();
    void attention();
    void getInformation(QString &, QString &, QString &);

private slots:
    void on_cancel_clicked();
    void on_ok_clicked();

signals:
    void checkConnectionDB();

private:
    Ui::ConnectDB *ui;
    QString nameDB;
    QString login;
    QString password;
};

#endif // CONNECTDB_H
