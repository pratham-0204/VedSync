#ifndef ACTIVE_APPOINTMENT_H
#define ACTIVE_APPOINTMENT_H

#include <QMainWindow>
#include <dashboard_doctor.h>
namespace Ui {
class Active_appointment;
}

class Active_appointment : public QMainWindow
{
    Q_OBJECT

public:
    explicit Active_appointment(QWidget *parent = nullptr);
    Active_appointment(QWidget *parent = nullptr , int s = 0);
    ~Active_appointment();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Active_appointment *ui;
};

#endif // ACTIVE_APPOINTMENT_H
