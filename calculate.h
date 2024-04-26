#ifndef CALCULATE_H
#define CALCULATE_H

#include <QDialog>
#include "output.h"

namespace Ui {
class calculate;
}

class calculate : public QDialog
{
    Q_OBJECT

public:
    explicit calculate(QWidget *parent = nullptr);
    ~calculate();

private slots:
    void on_button_total_avg_score_clicked();

    void on_pushButton_calc_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_statisc_clicked();

    void on_pushButton_Updatedata_clicked();

    void on_pushButton_nextpage_clicked();

    void on_pushButton_nextpage_2_clicked();

private:
    Ui::calculate *ui;
    void addRowToTable(const QString &grade, int count, int totalStudents, int row);
    int totalStudents;

};

#endif // CALCULATE_H
