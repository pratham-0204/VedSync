#include "prescription.h"
#include "ui_prescription.h"

prescription::prescription(QWidget *parent , QString s) :
    QMainWindow(parent),
    ui(new Ui::prescription)
{
    ui->setupUi(this);
    ui->textEdit->setText(s);
}

prescription::~prescription()
{
    delete ui;
}

void prescription::on_pushButton_clicked()
{
    this->close();
}

