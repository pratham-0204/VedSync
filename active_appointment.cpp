#include "active_appointment.h"
#include "ui_active_appointment.h"
#include "DEFINITIONS.h"

Active_appointment::Active_appointment(QWidget *parent , int s) :
    QMainWindow(parent),
    ui(new Ui::Active_appointment)
{
    ui->setupUi(this);
    ui->label->setText(QString::number(s));
}

Active_appointment::~Active_appointment()
{
    delete ui;
}

void Active_appointment::on_pushButton_clicked()
{
    this->close();
    Dashboard_doctor * w = new Dashboard_doctor(this , "");
    w->show();
}

