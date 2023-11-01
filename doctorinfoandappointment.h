#ifndef DOCTORINFOANDAPPOINTMENT_H
#define DOCTORINFOANDAPPOINTMENT_H

#include <QMainWindow>
#include <dashboard_patient.h>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
namespace Ui {
class DoctorInfoAndAppointment;
}

class DoctorInfoAndAppointment : public QMainWindow
{
    Q_OBJECT

public:
    explicit DoctorInfoAndAppointment(QWidget *parent = nullptr);
    DoctorInfoAndAppointment(QWidget *parent = nullptr , QString arr[] = {});
    ~DoctorInfoAndAppointment();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::DoctorInfoAndAppointment *ui;
};

#endif // DOCTORINFOANDAPPOINTMENT_H
