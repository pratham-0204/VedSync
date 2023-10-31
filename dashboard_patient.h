#ifndef DASHBOARD_PATIENT_H
#define DASHBOARD_PATIENT_H
#include<QListWidgetItem>
#include <QMainWindow>
#include "mainwindow.h"
#include "signin.h"
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include<doctorinfoandappointment.h>
namespace Ui {
class Dashboard_patient;
}

class Dashboard_patient : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard_patient(QWidget *parent = nullptr );
    Dashboard_patient(QWidget *parent = nullptr , QString = "patient" , QString = "name");
    ~Dashboard_patient();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::Dashboard_patient *ui;
};

#endif // DASHBOARD_PATIENT_H
