#include "dashboard_doctor.h"
#include "ui_dashboard_doctor.h"
#include <QListWidgetItem>
#include "DEFINITIONS.h"

Dashboard_doctor::Dashboard_doctor(QWidget *parent , QString s) :
    QMainWindow(parent),
    ui(new Ui::Dashboard_doctor)
{
    ui->setupUi(this);
}

Dashboard_doctor::~Dashboard_doctor()
{
    delete ui;
}




void Dashboard_doctor::on_pushButton_clicked()
{
    this->close();
    MainWindow * w = new MainWindow;
    w->show();
}


void Dashboard_doctor::on_listWidget_itemClicked(QListWidgetItem *item)
{
//    void Dashboard_doctor::on_listWidget_currentRowChanged(int currentRow)
//    {
//        ui->label->setText(QString::number(currentRow));
//        this->close();
//        MainWindow * w = new MainWindow;
//        w->show();

//    }
    ui->label->setText(QString::number(ui->listWidget->currentRow()));
    this->close();
    Active_appointment * w = new Active_appointment( this ,ui->listWidget->currentRow());
    w->show();

}



