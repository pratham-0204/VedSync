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

vector<QString> pdoc;
vector<QString> dname;
vector<QString> sheduleddname;
vector<QString> sheduleddoc;
vector<QString> prescriptions;
vector<QString> historytime;
vector<QString> sheduledtime;
vector<QString> vspecialization;
Dashboard_patient::Dashboard_patient(QWidget *parent , QString q , QString name) :
    QMainWindow(parent),
    ui(new Ui::Dashboard_patient)
{
    ui->setupUi(this);
    pacid =q;
    paname = name;
    ui->label->setText(paname);
    QString specialization = ui->specializaiton->text();
    QString city = ui->city->text();
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QDir::toNativeSeparators(CURRENT);
    mydb.setDatabaseName(path);
    if(mydb.open()){
        QSqlQuery query;
        query.prepare("SELECT * FROM appointments WHERE pid = :pid AND prescription IS NOT NULL");
        query.bindValue(":pid", pacid);

        if (query.exec() && query.next()) {
            while (query.next()) {
                // Retrieve data from the query result
                pdoc.push_back(query.value(0).toString());
                prescriptions.push_back(query.value(2).toString());
                historytime.push_back(query.value(3).toString());
                // Process the retrieved data as needed
            }
        }


        query.prepare("select name from doctors where did = :id");
        for(int i = 0 ; i < pdoc.size() ; i++){
            query.bindValue(":id", pdoc[i]);
            if (query.exec() && query.next()) {
                dname.push_back(query.value(0).toString());
            }
        }

        // Insert Data into appointments
        for(int i = 0 ; i < dname.size() ; i++){
            ui->listWidget_3->addItem(dname[i]+" "+historytime[i]);
        }

        query.prepare("SELECT * FROM appointments WHERE pid = :pid AND prescription IS NULL");
        query.bindValue(":pid", pacid);
        if (query.exec()) {
            while (query.next()) {
                // Retrieve data from the query result
                sheduleddoc.push_back(query.value(0).toString());
                sheduledtime.push_back(query.value(3).toString());

                // Process the retrieved data as needed
            }
        }

        query.prepare("select * from doctors where did = :id");
        for(int i = 0 ; i < sheduleddoc.size() ; i++){
            query.bindValue(":id", sheduleddoc[i]);
            if (query.exec() && query.next()) {
                sheduleddname.push_back(query.value(1).toString());
                vspecialization.push_back(query.value(4).toString());
            }
        }

        // Insert Data into appointments
        for(int i = 0 ; i < sheduleddname.size() ; i++){
            ui->listWidget_2->addItem(sheduleddname[i]+" "+sheduledtime[i]);
        }
        if(sheduleddname.size() >0){
        ui->label_16->setText(sheduleddname[0]);
        ui->label_17->setText(sheduleddoc[0]);
        ui->label_18->setText(vspecialization[0]);
        ui->label_19->setText(sheduledtime[0]);
        }


        mydb.close();
    }
    else{
        QMessageBox::information(this , "" , "NOT OPEN");
    }

}

Dashboard_patient::~Dashboard_patient()
{
    delete ui;
}

void Dashboard_patient::on_pushButton_2_clicked()
{
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();
    pdoc.clear();
    dname.clear();
    sheduleddname.clear();
    sheduleddoc.clear();
    prescriptions.clear();
    historytime.clear();
    sheduledtime.clear();
    vspecialization.clear();
    pdoc = std::vector<QString>();
    dname = std::vector<QString>();
    sheduleddname = std::vector<QString>();
    sheduleddoc = std::vector<QString>();
    prescriptions = std::vector<QString>();
    historytime = std::vector<QString>();
    sheduledtime = std::vector<QString>();
    vspecialization = std::vector<QString>();

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
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();
    pdoc.clear();
    dname.clear();
    sheduleddname.clear();
    sheduleddoc.clear();
    prescriptions.clear();
    historytime.clear();
    sheduledtime.clear();
    vspecialization.clear();
    pdoc = std::vector<QString>();
    dname = std::vector<QString>();
    sheduleddname = std::vector<QString>();
    sheduleddoc = std::vector<QString>();
    prescriptions = std::vector<QString>();
    historytime = std::vector<QString>();
    sheduledtime = std::vector<QString>();
    vspecialization = std::vector<QString>();

    int index = ui->listWidget->currentRow();
    QString arr[] = {pacid , paname , vid[index]};
    this->hide();
    DoctorInfoAndAppointment * w = new DoctorInfoAndAppointment(this , arr);
    w->show();
}


void Dashboard_patient::on_listWidget_3_itemClicked(QListWidgetItem *item)
{
    int index = ui->listWidget_3->currentRow();
    prescription * obj = new prescription(this , prescriptions[index]);
    obj->show();

}

