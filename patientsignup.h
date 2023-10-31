#ifndef PATIENTSIGNUP_H
#define PATIENTSIGNUP_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <signup.h>
#include <signin.h>
namespace Ui {
class patientsignup;
}

class patientsignup : public QMainWindow
{
    Q_OBJECT

public:
    explicit patientsignup(QWidget *parent = nullptr);
    ~patientsignup();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::patientsignup *ui;
};

#endif // PATIENTSIGNUP_H
