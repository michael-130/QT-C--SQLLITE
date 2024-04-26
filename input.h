// input.h
#ifndef INPUT_H
#define INPUT_H

#include <QDialog>
#include "calculate.h"
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class input; }
QT_END_NAMESPACE

class input : public QDialog
{
    Q_OBJECT

public:
    input(QWidget *parent = nullptr);
    ~input();

private slots:

    void pushButton_save_clicked();

    void on_pushButton_edit_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_sortbyname_clicked();

    void on_pushButton_sortbyid_clicked();

    void on_pushButton_clear_clicked();

    void on_button_total_avg_score_clicked();

    void on_pushButton_clicked();

private:
    Ui::input *ui;
};

#endif // INPUT_H
