#ifndef OUTPUT_H
#define OUTPUT_H

#include <QDialog>
#include "calculate.h"


namespace Ui {
class output;
}

class output : public QDialog
{
    Q_OBJECT

public:
    explicit output(QWidget *parent = nullptr);
    ~output();

private slots:
    void on_pushButton_loadtable_clicked();

    void on_pushButton_clicked();

    void on_pushButtonwrite_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_READ_clicked();

    void on_pushButtonwrite_2_clicked();

private:
    Ui::output *ui;

};

#endif // OUTPUT_H
