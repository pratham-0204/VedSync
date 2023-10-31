#ifndef DOCTORINFOANDAPPOINTMENT_H
#define DOCTORINFOANDAPPOINTMENT_H

#include <QMainWindow>

namespace Ui {
class DoctorInfoAndAppointment;
}

class DoctorInfoAndAppointment : public QMainWindow
{
    Q_OBJECT

public:
    explicit DoctorInfoAndAppointment(QWidget *parent = nullptr);
    ~DoctorInfoAndAppointment();

private:
    Ui::DoctorInfoAndAppointment *ui;
};

#endif // DOCTORINFOANDAPPOINTMENT_H
