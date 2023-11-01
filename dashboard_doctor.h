#ifndef DASHBOARD_DOCTOR_H
#define DASHBOARD_DOCTOR_H
#include<QListWidgetItem>
#include <QMainWindow>
#include <mainwindow.h>
#include <active_appointment.h>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class Dashboard_doctor;
}

class Dashboard_doctor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard_doctor(QWidget *parent = nullptr);
    Dashboard_doctor(QWidget * parent = nullptr , QString s ="doctor");
    ~Dashboard_doctor();

private slots:
    void on_pushButton_clicked();


    void on_Mark_btn_clicked();

private:
    Ui::Dashboard_doctor *ui;
    void closeAllQueriesAndTransactions();
    void update_window();
};

#endif // DASHBOARD_DOCTOR_H
