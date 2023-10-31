#ifndef DASHBOARD_PATIENT_H
#define DASHBOARD_PATIENT_H
#include<QListWidgetItem>
#include <QMainWindow>
#include "mainwindow.h"
#include "signin.h"
namespace Ui {
class Dashboard_patient;
}

class Dashboard_patient : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard_patient(QWidget *parent = nullptr );
    Dashboard_patient(QWidget *parent = nullptr , QString = "patient");
    ~Dashboard_patient();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Dashboard_patient *ui;
};

#endif // DASHBOARD_PATIENT_H
