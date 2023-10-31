#ifndef DOCTORSIGNUP_H
#define DOCTORSIGNUP_H

#include <QMainWindow>
#include <signin.h>
#include <signup.h>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QTime>

namespace Ui {
class doctorsignup;
}

class doctorsignup : public QMainWindow
{
    Q_OBJECT

public:
    explicit doctorsignup(QWidget *parent = nullptr);
    ~doctorsignup();

private slots:
    void on_pushButton_2_clicked();


    void on_pushButton_clicked();

private:
    Ui::doctorsignup *ui;
    int rating,availability;
    QString name,gender,specialization,email,clinicname,clinicaddress,licence,password,cpassword,did,age,fees;
    QTime s1f,s2f,s1t,s2t;
    QSqlDatabase mydb;
};

#endif // DOCTORSIGNUP_H
