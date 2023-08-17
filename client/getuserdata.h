#ifndef GETUSERDATA_H
#define GETUSERDATA_H

#include <QDialog>
#include "authentication.h"

namespace Ui {
class GetUserData;
}

class GetUserData : public QDialog
{
    Q_OBJECT

public:
    explicit GetUserData(QWidget *parent = nullptr);
    void getPtrAuthentication(Authentication*);
    ~GetUserData();
    void getUserData(QString &, QString &, char &);
    void setType(char);
    void clearForm();

private slots:
    void on_Ok_clicked();
    void on_cancel_clicked();

signals:
    void sendUserData();
    void cancelClicked();

private:
    Ui::GetUserData *ui;
    QString login;
    QString password;
    char type;
};

#endif // GETUSERDATA_H
