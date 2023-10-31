#include "usersignin.h"
#include "ui_usersignin.h"
#include <QMessageBox>
#include "DEFINITIONS.h"
usersignin::usersignin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::usersignin)
{
    ui->setupUi(this);
}

usersignin::~usersignin()
{
    delete ui;
}

void usersignin::on_pushButton_clicked()
{
    this->close();
    MainWindow * w = new MainWindow;
    w->show();
}


void usersignin::on_pushButton_2_clicked()
{

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QDir::toNativeSeparators(CURRENT);
    mydb.setDatabaseName(path);
    if(!mydb.open()){
        QMessageBox::information(this,"connection info", "not connected");
    }
    else{
        QString id = ui->userid->text();
        QString password = ui->password->text();

        bool patient = false;
        bool doctor = false;
        QSqlQuery qry;
        qry.prepare("SELECT * FROM patients WHERE pid = :pid");
        qry.bindValue(":pid", id);


        if (qry.exec() && qry.next()) {
            // If a row is fetched, the PID exists
            patient = true;
        }
        qry.prepare("SELECT * FROM doctors WHERE did = :did");
        qry.bindValue(":did", id);


        if (qry.exec() && qry.next()) {
            // If a row is fetched, the PID exists
            doctor = true;
        }

        if(patient){
            QString dpassword;
            qry.prepare("SELECT * FROM patients WHERE pid = :pid");
            qry.bindValue(":pid", id);
            if(qry.exec() && qry.next()){
                dpassword = qry.value(6).toString();
            }
            else{
                QMessageBox::information(this , "" , "error occured");
            }
            if(dpassword.trimmed() == password.trimmed()){
                mydb.close();
                this->close();
//                QMessageBox::information(this , "" , "closed");
                Dashboard_patient *ww = new Dashboard_patient(this , id);
                ww->show();
//                QMessageBox::information(this , "" , "closed");

            }
            else{
                QMessageBox::information(this , "" , "the password is not correct ");
            }

        }
        else if(doctor){
            QString dpassword;
            qry.prepare("SELECT * FROM doctors WHERE did = :did");
            qry.bindValue(":did", id);
            if(qry.exec() && qry.next()){
                dpassword = qry.value(9).toString();
            }
            else{
                QMessageBox::information(this , "" , "error occured");
            }
            if(dpassword.trimmed() == password.trimmed()){
                mydb.close();
                this->close();
                Dashboard_doctor * ww = new Dashboard_doctor(this , id);
                ww->show();
            }
            else{
                QMessageBox::information(this , "" , "the password is not correct ");
            }

        }
        else{
            QMessageBox::information(this , "" , "account is not created");
        }
    }
}

