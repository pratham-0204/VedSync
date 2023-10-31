#include "doctorsignup.h"
#include "ui_doctorsignup.h"
#include "DEFINITIONS.h"
#include <QMessageBox>


doctorsignup::doctorsignup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::doctorsignup)
{
    ui->setupUi(this);
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QDir::toNativeSeparators(CURRENT);
    mydb.setDatabaseName(path);
}

doctorsignup::~doctorsignup()
{
    delete ui;
}

// BACK BUTTON
void doctorsignup::on_pushButton_2_clicked()
{
    this->close();
    signup * w = new signup;
    w->show();
}


// SIGNUP BUTTON
void doctorsignup::on_pushButton_clicked()
{

    if(!mydb.open()){
        QMessageBox::information(this,"Connection Info", "Not Connected");
    }
    else{
        name = ui->Name->text();
        gender = ui->Gender->text();
        specialization = ui->Specialization->text();
        email = ui->Email->text();
        clinicname = ui->Clinic_Name->text();
        clinicaddress = ui->Address->text();
        licence = ui->License->text();
        password = ui->Password->text();
        cpassword = ui->cPassword->text();
        did = ui->Phone->text();
        age = ui->Age->text();
        fees = ui->Fees->text();
        rating = 0;
        availability = 1;
        s1f = ui->s1f->time();
        s2f = ui->s2f->time();
        s1t = ui->s1t->time();
        s2t = ui->s2t->time();

        QSqlQuery qry;
        qry.prepare("INSERT INTO doctors VALUES (:did,:name,:age,:gender,:specialization,:email,:clinicname,:clinicaddress,:license,:password,:fees,:s1f,:s1t,:s2f,:s2t,:rating,:availability)");
        qry.bindValue(":did",did);
        qry.bindValue(":name",name);
        qry.bindValue(":age",age);
        qry.bindValue(":gender",gender);
        qry.bindValue(":specialization",specialization);
        qry.bindValue(":email",email);
        qry.bindValue(":clinicname",clinicname);
        qry.bindValue(":clinicaddress",clinicaddress);
        qry.bindValue(":license",licence);
        qry.bindValue(":password",password);
        qry.bindValue(":fees",fees);
        qry.bindValue(":s1f",s1f);
        qry.bindValue(":s1t",s1t);
        qry.bindValue(":s2f",s2f);
        qry.bindValue(":s2t",s2t);
        qry.bindValue(":rating",rating);
        qry.bindValue(":availability",availability);

        if (did != "" && did.length() == 10 /*&& name !="" && gender != "" && age!= "" && specialization != "" && email != ""  && clinicname != "" && clinicaddress != "" && licence != "" && fees!="" */){
            if (password == cpassword){
                if(qry.exec()){
                    QMessageBox::information(this , "SUCCESS" , "Account Created Succussfully");
                }
                else{
                    QMessageBox::information(this , "FAILED" , "Account Not Created");
                }
                mydb.close();

                this->close();
                MainWindow * w = new MainWindow;
                w->show();

            }else{
                QMessageBox::information(this,"Password Mismatch","Passwords do not match");
            }
        } else {
            QMessageBox::information(this,"Missing Value","Please fill all fields");
        }


    }
}

