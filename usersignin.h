#ifndef USERSIGNIN_H
#define USERSIGNIN_H

#include <QMainWindow>
#include <mainwindow.h>
#include<dashboard_doctor.h>
#include<dashboard_patient.h>
#include<mainwindow.h>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
namespace Ui {
class usersignin;
}

class usersignin : public QMainWindow
{
    Q_OBJECT

public:
    explicit usersignin(QWidget *parent = nullptr);
    ~usersignin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::usersignin *ui;
};

#endif // USERSIGNIN_H
