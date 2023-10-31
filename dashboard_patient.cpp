#include "dashboard_patient.h"
#include "ui_dashboard_patient.h"
#include <QListWidgetItem>
#include "DEFINITIONS.h"

//QString docid;
Dashboard_patient::Dashboard_patient(QWidget *parent , QString q) :
    QMainWindow(parent),
    ui(new Ui::Dashboard_patient)
{
    ui->setupUi(this);
//    docid = s;
    ui->label->setText(q);
}

Dashboard_patient::~Dashboard_patient()
{
    delete ui;
}

void Dashboard_patient::on_pushButton_2_clicked()
{
    this->close();
    MainWindow * w = new MainWindow;
    w->show();
}

