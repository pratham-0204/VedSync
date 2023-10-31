#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include <QMainWindow>

namespace Ui {
class prescription;
}

class prescription : public QMainWindow
{
    Q_OBJECT

public:
    explicit prescription(QWidget *parent = nullptr , QString s = "");
    ~prescription();

private slots:
    void on_pushButton_clicked();

private:
    Ui::prescription *ui;
};

#endif // PRESCRIPTION_H
