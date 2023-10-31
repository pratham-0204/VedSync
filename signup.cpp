#include "signup.h"
#include "ui_signup.h"
#include "DEFINITIONS.h"

signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
}

signup::~signup()
{
    delete ui;
}

void signup::on_pushButton_clicked()
{
    this->close();
    doctorsignup * w = new doctorsignup;
    w->show();
}


void signup::on_pushButton_2_clicked()
{
    this->hide();
    patientsignup * w = new patientsignup;
    w->show();
}


void signup::on_pushButton_3_clicked()
{
    this->close();
    MainWindow * w = new MainWindow;
    w->show();
}

