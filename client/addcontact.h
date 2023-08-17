#ifndef ADDCONTACT_H
#define ADDCONTACT_H

#include <QDialog>
#include <QListWidgetItem>
#include "chat.h"

namespace Ui {
class addContact;
}

class AddContact : public QDialog
{
    Q_OBJECT

public:
    explicit AddContact(QWidget *parent = nullptr);
    ~AddContact();
    void setUsersList(QSet<QString> &, QMap<QString, Chat> &, QString &);
    void getSelectContact(QString &);

private slots:
    void on_add_clicked();
    void on_listUsers_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

signals:
    void addNewContact();

private:
    Ui::addContact *ui;
    QListWidgetItem * selectContact;
};

#endif // ADDCONTACT_H
