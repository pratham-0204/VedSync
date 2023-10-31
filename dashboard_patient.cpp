#include "dashboard_patient.h"
#include "ui_dashboard_patient.h"
#include <QListWidgetItem>
#include "DEFINITIONS.h"
#include <vector>
#include<QMessageBox>
using namespace std;
QString pacid;
QString paname;
vector<QString> vname;
vector<QString> vid;
Dashboard_patient::Dashboard_patient(QWidget *parent , QString q , QString name) :
    QMainWindow(parent),
    ui(new Ui::Dashboard_patient)
{
    ui->setupUi(this);
    pacid =q;
    paname = name;
    ui->label->setText(paname);
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


void Dashboard_patient::on_pushButton_clicked()
{
    QString specialization = ui->specializaiton->text();
    QString city = ui->city->text();
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QDir::toNativeSeparators(CURRENT);
    mydb.setDatabaseName(path);
    ui->listWidget->clear();
    QSqlQuery qry;
    mydb.open();
    if(specialization != ""){
        int c = 0;
        if(city.trimmed() == ""){
            qry.prepare("SELECT * FROM doctors WHERE specialization = :specialization");
            qry.bindValue(":specialization", specialization);
            if(qry.exec()){
                while(qry.next()){
                    vid.push_back(qry.value(0).toString());
                    vname.push_back(qry.value(1).toString());
                    ui->listWidget->addItem(qry.value(1).toString());
                    c++;
                }
            }
            else{
                QMessageBox::information(this , "" , "not executed");
            }

        }
        else{
            qry.prepare("SELECT * FROM doctors WHERE clinicaddress = :city AND specialization = :specialization");
            qry.bindValue(":city", city);
            qry.bindValue(":specialization", specialization);
            if(qry.exec()){
                while(qry.next()){
                    vid.push_back(qry.value(0).toString());
                    vname.push_back(qry.value(1).toString());
                     ui->listWidget->addItem(qry.value(1).toString());

                    c++;
                }
            }
        }
        mydb.close();
    }



}


void Dashboard_patient::on_listWidget_itemClicked(QListWidgetItem *item)
{
    int index = ui->listWidget->currentRow();
    QString arr[] = {pacid , paname , vid[index]};
    this->hide();
    DoctorInfoAndAppointment * w = new DoctorInfoAndAppointment(this , arr);
    w->show();
}

