#include "dashboard_doctor.h"
#include "ui_dashboard_doctor.h"
#include <QListWidgetItem>
#include "DEFINITIONS.h"
#include <QMessageBox>
#include <vector>
using namespace std;

QString id;
vector<QString> p_id;
vector<QString> p_name,p_age,p_gender,past_record;

Dashboard_doctor::Dashboard_doctor(QWidget *parent , QString s) :
    QMainWindow(parent),
    ui(new Ui::Dashboard_doctor)
{
    ui->setupUi(this);
    ui->radioButton_2->setChecked(true);
    id = s;
    QSqlDatabase::removeDatabase("qt_sql_default_connection");
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QDir::toNativeSeparators(CURRENT);
    mydb.setDatabaseName(path);

    if(!mydb.open()){
        QMessageBox::information(this,"Connection info", "Not Connected");
    }
    else{
        QSqlQuery qry;
        qry.prepare("SELECT * FROM doctors WHERE did = :did ");
        qry.bindValue(":did", id);

        if (qry.exec() && qry.next()) {
            ui->Doctor_name->setText(qry.value(1).toString());
            ui->doctor_id->setText(id);
        }

        // Fetch data to insert into appointments
        qry.prepare("select pid from appointments where did = :id and prescription IS NULL");
        qry.bindValue(":id", id);

        if (qry.exec()) {
            while(qry.next()){
                p_id.push_back(qry.value(0).toString());
            }
        }

        // Fetch names from patients table to insert into appointments
        qry.prepare("select name,age,gender from patients where pid = :id");
        for(int i = 0 ; i < p_id.size() ; i++){
            qry.bindValue(":id", p_id[i]);
            if (qry.exec() && qry.next()) {
                p_name.push_back(qry.value(0).toString());
                p_age.push_back(qry.value(1).toString());
                p_gender.push_back(qry.value(2).toString());
            }
        }

        // Fetch Data to insert into Past Records
        qry.prepare("select pid,dateandtime from appointments where did = :id and prescription IS NOT NULL ORDER BY dateandtime DESC");
        qry.bindValue(":id", id);
        if (qry.exec()) {
            while(qry.next()){
                past_record.push_back(qry.value(0).toString()+" "+qry.value(1).toString());
            }
        }

        // Insert Data into appointments
        for(int i = 0 ; i < p_name.size() ; i++){
            ui->apointments->addItem(p_id[i]+" "+p_name[i]);
        }

        // Insert Data into Current Patient
        ui->Patient_name->setText(p_name[0]);
        ui->p_id->setText(p_id[0]);
        ui->p_age_label->setText(p_age[0]);
        ui->p_gender_label->setText(p_gender[0]);

        // Insert Data into Past Records
        for(int i = 0 ; i < past_record.size() ; i++){
            ui->patient_history->addItem(past_record[i]);
        }

    }

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

    ui->label->setText(QString::number(ui->apointments->currentRow()));
    this->close();
    Active_appointment * w = new Active_appointment( this ,ui->apointments->currentRow());
    w->show();

}



