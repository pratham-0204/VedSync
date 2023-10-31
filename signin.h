#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>
#include<dashboard_doctor.h>
#include<dashboard_patient.h>
#include<mainwindow.h>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
namespace Ui {
class welcomepage;
}

class welcomepage : public QDialog
{
    Q_OBJECT

public:
    explicit welcomepage(QWidget *parent = nullptr);
    ~welcomepage();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::welcomepage *ui;
};

#endif // SIGNIN_H
