#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DEFINITIONS.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent) ,
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//  the next three lines are used to connect database
//    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
//    QString path = QDir::toNativeSeparators("./VedSync.db");
//    mydb.setDatabaseName(path);

//    if (!mydb.open())
//        ui->label->setText("Failed to open the database");
//    else
//        ui->label->setText("Connected.... ");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    close();
    signup obj;
    obj.exec();

}


void MainWindow::on_pushButton_clicked()
{
    this ->close();
    usersignin *obj  = new usersignin;
    obj->show();
}

