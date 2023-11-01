#include "dashboard_doctor.h"
#include "ui_dashboard_doctor.h"
#include <QListWidgetItem>
#include "DEFINITIONS.h"
#include <QMessageBox>
#include <vector>
using namespace std;

QString id;
vector<QString> p_id,p_name,p_age,p_gender,past_record,p_datetime;

Dashboard_doctor::Dashboard_doctor(QWidget *parent , QString s) :
    QMainWindow(parent),
    ui(new Ui::Dashboard_doctor)
{
    ui->setupUi(this);
    ui->radioButton_2->setChecked(true);
    id = s;
    update_window();
}

Dashboard_doctor::~Dashboard_doctor()
{
    delete ui;

}



// Logout Button
void Dashboard_doctor::on_pushButton_clicked()
{
    closeAllQueriesAndTransactions();


    p_id.clear();
    p_name.clear();
    p_age.clear();
    p_gender.clear();
    past_record.clear();
    p_datetime.clear();

    p_id = vector<QString>();
    p_name = vector<QString>();
    p_age = vector<QString>();
    p_gender = vector<QString>();
    past_record = vector<QString>();
    p_datetime = vector<QString>();

    ui->apointments->clear();
    ui->patient_history->clear();

    this->close();
    MainWindow * w = new MainWindow;
    w->show();
}


void Dashboard_doctor::closeAllQueriesAndTransactions(){
    QSqlDatabase::database().commit();
    QSqlDatabase::database().close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

void Dashboard_doctor::update_window(){
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
        QSqlDatabase::database().commit();

        // Fetch data from TABLE appointments to insert into appointments
        qry.prepare("select pid,dateandtime from appointments where did = :id and prescription IS NULL");
        qry.bindValue(":id", id);

        if (qry.exec()) {
            while(qry.next()){
                p_id.push_back(qry.value(0).toString());
                p_datetime.push_back(qry.value(1).toString());
            }
        }
        QSqlDatabase::database().commit();

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
        QSqlDatabase::database().commit();

        // Fetch Data to insert into Past Records
        qry.prepare("select pid,dateandtime from appointments where did = :id and prescription IS NOT NULL ORDER BY dateandtime DESC");
        qry.bindValue(":id", id);
        if (qry.exec()) {
            while(qry.next()){
                past_record.push_back(qry.value(0).toString()+" "+qry.value(1).toString());
            }
        }
        QSqlDatabase::database().commit();

        // Insert Data into appointments
        for(int i = 0 ; i < p_name.size() ; i++){
            ui->apointments->addItem(p_id[i]+" "+p_name[i]);
        }

        // Insert Data into Current Patient
        if (p_name.size() > 0){
            ui->Patient_name->setText(p_name[0]);
            ui->p_id->setText(p_id[0]);
            ui->p_age_label->setText(p_age[0]);
            ui->p_gender_label->setText(p_gender[0]);
        }

        // Insert Data into Past Records
        for(int i = 0 ; i < past_record.size() ; i++){
            ui->patient_history->addItem(past_record[i]);
        }


    }
};


void Dashboard_doctor::on_Mark_btn_clicked()
{
    QSqlQuery qry;
    qry.prepare("UPDATE appointments SET prescription = :prescription WHERE dateandtime = :dateandtime");
    qry.bindValue(":did", id);
    qry.bindValue(":prescription", ui->prescription_input->toPlainText());
    qry.bindValue(":dateandtime", p_datetime[0]);
    if (qry.exec()) {
        QMessageBox::information(this,"Success", "Prescription Marked");
    }
    else{
        QMessageBox::information(this,"Error", "Prescription Not Marked");
    }
    closeAllQueriesAndTransactions();


    p_id.clear();
    p_name.clear();
    p_age.clear();
    p_gender.clear();
    past_record.clear();
    p_datetime.clear();

    p_id = vector<QString>();
    p_name = vector<QString>();
    p_age = vector<QString>();
    p_gender = vector<QString>();
    past_record = vector<QString>();
    p_datetime = vector<QString>();

    ui->apointments->clear();
    ui->patient_history->clear();
    ui->prescription_input->clear();

    update_window();
}


void Dashboard_doctor::on_apointments_itemClicked(QListWidgetItem *item)
{
    int index = ui->apointments->currentRow();
    Active_appointment * w = new Active_appointment(this , p_id[index]);
    w->show();
}

