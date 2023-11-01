#include "patientsignup.h"
#include "ui_patientsignup.h"
#include <QMessageBox>
#include <iostream>
#include "DEFINITIONS.h"

using namespace std;
patientsignup::patientsignup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::patientsignup)
{
    ui->setupUi(this);


}

patientsignup::~patientsignup()
{
    delete ui;
}

void patientsignup::on_pushButton_clicked()
{
    this->close();
    signup * w = new signup;
    w->show();
}


void patientsignup::on_pushButton_2_clicked()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QDir::toNativeSeparators(CURRENT);
    mydb.setDatabaseName(path);
    if(!mydb.open()){
        QMessageBox::information(this,"Connection Info", "Not Connected");
    }
    else{

        QString id = ui->phone->text();
        QString name = ui->name->text();
        QString gender = ui->gender->text();
        QString age = ui->age->text();
        QString address = ui->address->text();
        QString email = ui->email->text();
        QString password = ui->password->text();
        QString cpassword = ui->cpassword->text();

        if(ui->phone->text() != "" && id.length() == 10){
            if(password == cpassword){
                QSqlQuery qry;

                qry.prepare("SELECT * FROM patients WHERE pid = :pid");
                qry.bindValue(":pid", id);

                bool flag = true;

                if (qry.exec() && qry.next()) {
                    // If a row is fetched, the PID exists
                    flag = false;
                } else {
                    qDebug() << "PID does not exist in the table.";
                }
                if(flag){
    //                qry.prepare("insert into patients values('1234567890' , 'pratham' , '33' , 'male' , 'beawar' , '@gmail.com' , 'prathamsharma')");
                    qry.prepare("INSERT INTO patients VALUES (:id, :name, :age, :gender, :address, :email, :password)");

                    qry.bindValue(":id", id);
                    qry.bindValue(":name", name);
                    qry.bindValue(":age", age);
                    qry.bindValue(":gender", gender);
                    qry.bindValue(":address", address);
                    qry.bindValue(":email", email);
                    qry.bindValue(":password", password);
                    if(qry.exec()){
                        QMessageBox::information(this , "" , "Account Created Succussfully");
                    }
                    else{
                        QMessageBox::information(this , "Not Done" , "Failed to create account! \nPlease try again");
                    }
                    mydb.close();
                    this->close();
                    MainWindow * w = new MainWindow;
                    w->show();

                }
                else{
                    QMessageBox::information(this , "Error" , "The user is already registered");
                }
            }

            else{
                QMessageBox::information(this , "Error" , "Passwords do not match");
            }
        }
        else{
            QMessageBox::information(this , "Error" ,"Please fill all the deatils completely");
        }
        mydb.close();
    }
}

