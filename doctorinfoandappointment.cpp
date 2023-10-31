#include "doctorinfoandappointment.h"
#include "ui_doctorinfoandappointment.h"
#include "DEFINITIONS.h"

QString arrr[3];

DoctorInfoAndAppointment::DoctorInfoAndAppointment(QWidget *parent , QString arr[]) :
    QMainWindow(parent),
    ui(new Ui::DoctorInfoAndAppointment)
{
    ui->setupUi(this);
    for(int i = 0 ; i < 3 ; i++){
        arrr[i] = arr[i];
    }
    ui->label->setText(arr[2]);
}

DoctorInfoAndAppointment::~DoctorInfoAndAppointment()
{
    delete ui;
}

void DoctorInfoAndAppointment::on_pushButton_2_clicked()
{
    this->close();
    Dashboard_patient * w = new Dashboard_patient(this , arrr[0] , arrr[1]);
    w->show();
}

