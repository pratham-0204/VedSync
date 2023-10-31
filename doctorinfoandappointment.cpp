#include "doctorinfoandappointment.h"
#include "ui_doctorinfoandappointment.h"
#include "DEFINITIONS.h"

DoctorInfoAndAppointment::DoctorInfoAndAppointment(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DoctorInfoAndAppointment)
{
    ui->setupUi(this);
}

DoctorInfoAndAppointment::~DoctorInfoAndAppointment()
{
    delete ui;
}
