#include "doctorinfoandappointment.h"
#include "ui_doctorinfoandappointment.h"
#include "DEFINITIONS.h"
#include <QDate>
#include <QDateTime>
#include <QMessageBox>
#include <QVariant>

QString arrr[3];
QString docid;
//QString pacid;
DoctorInfoAndAppointment::DoctorInfoAndAppointment(QWidget *parent , QString arr[]) :
    QMainWindow(parent),
    ui(new Ui::DoctorInfoAndAppointment)
{
    ui->setupUi(this);
    for(int i = 0 ; i < 3 ; i++){
        arrr[i] = arr[i];
    }
//    QDateTime currentDateTime = QDateTime::currentDateTime();
//    QString currentDateTimeString = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");
//    ui->fees->setText(currentDateTimeString);
    docid = arr[2];
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QDir::toNativeSeparators(CURRENT);
    mydb.setDatabaseName(path);
    QSqlQuery qry;
//    pacid = arr[0];
    if(mydb.open()){
        qry.prepare("select * from doctors where did = '"+docid+"'");
        if(qry.exec()&&qry.next()){
            if(qry.value(14).toString() == "1"){
                ui->pushButton->setEnabled(true);
                ui->pushButton->setText("Reserve Appointment");

                ui->phone->setText(qry.value(0).toString());
                ui->email->setText(qry.value(5).toString());
                ui->fees->setText(qry.value(10).toString());
                ui->gender->setText(qry.value(3).toString());
                ui->clinicaddress->setText(qry.value(7).toString());
                ui->clinicname->setText(qry.value(6).toString());
                ui->rating->setText(qry.value(13).toString());
                ui->specialization->setText(qry.value(4).toString());
                ui->label->setText(qry.value(1).toString());
                ui->name->setText(qry.value(1).toString());
            }
        }
    }
    else{
        QMessageBox::information(this , "" , "not opened");
    }
    mydb.close();

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


void DoctorInfoAndAppointment::on_pushButton_clicked()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QDir::toNativeSeparators(CURRENT);
    mydb.setDatabaseName(path);
    QSqlQuery doctorQuery;
    if(mydb.open()){

        // Get Start and end time
        doctorQuery.prepare("SELECT s1f, s1t FROM doctors WHERE did = :doctorId");
        doctorQuery.bindValue(":doctorId", docid);
        if (!doctorQuery.exec() || !doctorQuery.next()) {
            qDebug() << "Doctor not found.";
            return;
        }
        QTime doctorStartTime = doctorQuery.value(0).toTime();
        QTime doctorEndTime = doctorQuery.value(1).toTime();

        // Calculate the next available appointment time (with a 10-minute gap).
        QSqlQuery lastAppointmentQuery;
        lastAppointmentQuery.prepare("SELECT MAX(dateandtime) FROM appointments WHERE did = :doctorId");
        lastAppointmentQuery.bindValue(":doctorId", docid);

        // Add 10 min to last datetime
        QDateTime desiredDateTime;
        if (lastAppointmentQuery.exec() && lastAppointmentQuery.next()) {
            QDateTime lastAppointmentDateTime = lastAppointmentQuery.value(0).toDateTime();
            QDateTime nextAppointmentDateTime = lastAppointmentDateTime.addSecs(600);  // 10 minutes in seconds

            // If the next available appointment is within the doctor's working hours, use it.
            if (nextAppointmentDateTime.time() <= doctorEndTime) {
                desiredDateTime = nextAppointmentDateTime;
            } else {
                // If it's beyond the doctor's working hours, move to the next day and set it to the doctor's start time.
                desiredDateTime = nextAppointmentDateTime.addDays(1);
                desiredDateTime.setTime(doctorStartTime);
            }
        } else {
            // If no previous appointments exist for this doctor, set the appointment to the doctor's start time.
            desiredDateTime.setDate(QDate::currentDate().addDays(1));
            desiredDateTime.setTime(doctorStartTime);
        }

        // Insert the appointment into the database.
        QString outputDateTime = desiredDateTime.toString("yyyy-MM-dd HH:mm:ss");
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO appointments (did, pid,dateandtime) VALUES (:doctorId, :patientId, :appointmentDatetime)");
        insertQuery.bindValue(":doctorId", docid);
        insertQuery.bindValue(":patientId", arrr[0]);
        insertQuery.bindValue(":appointmentDatetime", outputDateTime);

        if (insertQuery.exec()) {
            QMessageBox::information(this , "" , "Your appointment is scheduled for "+outputDateTime);
        } else {
            qDebug() << "Failed to book the appointment.";
        }


    }
    else{
        QMessageBox::information(this , "" , "did not open");
    }
}

