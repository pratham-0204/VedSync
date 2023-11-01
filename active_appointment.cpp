#include "active_appointment.h"
#include "ui_active_appointment.h"
#include "DEFINITIONS.h"
#include <QMessageBox>

QString nid;

Active_appointment::Active_appointment(QWidget *parent , QString s) :
    QMainWindow(parent),
    ui(new Ui::Active_appointment)
{
    ui->setupUi(this);
    nid = s;

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
            qry.prepare("select * from pid where pid = '"+s+"'");
            if(qry.exec() && qry.next()){

            }
        }
    }
}

Active_appointment::~Active_appointment()
{
    delete ui;
}

void Active_appointment::on_pushButton_clicked()
{
    this->close();
    Dashboard_doctor * w = new Dashboard_doctor(this , "");
    w->show();
}

