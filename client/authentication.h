#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Authentication; }
QT_END_NAMESPACE

class Authentication : public QMainWindow
{
    Q_OBJECT

public:
    Authentication(QWidget *parent = nullptr);
    ~Authentication();
    void sleepServer();
    void openUserSpace(bool);
    void authorizationDisable(bool);
    void registrationDisable(bool);

private slots:
    void on_registration_clicked();
    void on_authorization_clicked();
    void on_openUserSpacse_clicked();

signals:
    void registrationClicked();
    void authorizationClicked();
    void openUserSpaceClicked();

private:
    Ui::Authentication *ui;
};
#endif // AUTHENTICATION_H
