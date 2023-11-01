#include "active_appointment.h"
#include "ui_active_appointment.h"
#include "DEFINITIONS.h"
#include <QMessageBox>

QString patid;
QString doctid;
Active_appointment::Active_appointment(QWidget *parent , QString s[]) :
    QMainWindow(parent),
    ui(new Ui::Active_appointment)
{
    ui->setupUi(this);
    patid = s[1];
    doctid = s[0];
    ui->p_name_label->setText(s[2]);
    ui->label_6->setText(patid);
    ui->a_date_label->setText(s[3]);
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QDir::toNativeSeparators(CURRENT);
    mydb.setDatabaseName(path);

    if(!mydb.open()){
        QMessageBox::information(this,"Connection info", "Not Connected");
    }
    else{
        QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
        QString path = QDir::toNativeSeparators(CURRENT);
        mydb.setDatabaseName(path);
        if(mydb.open()){
            QSqlQuery qry;
            qry.prepare("select * from appointments where pid = '"+patid+"' and did = '"+doctid+"' and prescription is not null");
            if(qry.exec()){
                while(qry.next()){
                    ui->listWidget_2->addItem(qry.value(3).toString());
                }
            }
        }
    }
    mydb.close();
}

Active_appointment::~Active_appointment()
{
    delete ui;
}

void Active_appointment::on_pushButton_clicked()
{
    this->close();

}

