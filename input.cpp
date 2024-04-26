#include "input.h"
#include "ui_input.h"
#include <QMessageBox>
#include "calculate.h"
input::input(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::input)
{
    ui->setupUi(this);
    QPixmap pix("C:/Qtproject/png/R.jpeg");
    ui->label_picture->setPixmap(pix);
    connect(ui->pushButton_save, &QPushButton::clicked, this, &input::pushButton_save_clicked);
    login conn;
    if (!conn.connOpen())
        ui->label_thirdpage_connection->setText("Failed to open the database");
    else
        ui->label_thirdpage_connection->setText("Connected....");
}

input::~input()
{
    delete ui;
}
// save button = save per collumn
void input::pushButton_save_clicked()
{
    login conn;
    QString Id, Name, Score1, Score2, Score3, Score4, Score5, Score6;
    Id = ui->txt_id->text();
    Name = ui->txt_name->text();
    Score1 = ui->txt_score_1->text();
    Score2 = ui->txt_score_2->text();
    Score3 = ui->txt_score_3->text();
    Score4 = ui->txt_score_4->text();
    Score5 = ui->txt_score_5->text();
    Score6 = ui->txt_score_6->text();

    if (!conn.connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery qry;
    qry.prepare("INSERT INTO Studentdata (Id, Name, \"Score 1\", \"Score 2\", \"Score 3\", \"Score 4\", \"Score 5\", \"Score 6\") "
                "VALUES (:Id, :Name, :Score1, :Score2, :Score3, :Score4, :Score5, :Score6)");

    qry.bindValue(":Id", Id);
    qry.bindValue(":Name", Name);
    qry.bindValue(":Score1", Score1);
    qry.bindValue(":Score2", Score2);
    qry.bindValue(":Score3", Score3);
    qry.bindValue(":Score4", Score4);
    qry.bindValue(":Score5", Score5);
    qry.bindValue(":Score6", Score6);



    if (qry.exec())
    {
        QMessageBox::information(this, tr("Saved"), tr("The data has been saved."));
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), qry.lastError().text());
    }

    conn.connClose();
}

// Edit button
void input::on_pushButton_edit_clicked()
{
    login conn;
    QString Id, Name, Score1, Score2, Score3, Score4, Score5, Score6;
    Id = ui->txt_id->text();
    Name = ui->txt_name->text();
    Score1 = ui->txt_score_1->text();
    Score2 = ui->txt_score_2->text();
    Score3 = ui->txt_score_3->text();
    Score4 = ui->txt_score_4->text();
    Score5 = ui->txt_score_5->text();
    Score6 = ui->txt_score_6->text();

    if (!conn.connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery qry;
    qry.prepare("UPDATE Studentdata SET Name = :Name, \"Score 1\" = :Score1, \"Score 2\" = :Score2, \"Score 3\" = :Score3, \"Score 4\" = :Score4,\"Score 5\" = :Score5,\"Score 6\" = :Score6 "
                "WHERE Id = :Id");


    qry.bindValue(":Id", Id);
    qry.bindValue(":Name", Name);
    qry.bindValue(":Score1", Score1);
    qry.bindValue(":Score2", Score2);
    qry.bindValue(":Score3", Score3);
    qry.bindValue(":Score4", Score4);
    qry.bindValue(":Score5", Score5);
    qry.bindValue(":Score6", Score6);

    if (qry.exec())
    {
        QMessageBox::information(this, tr("Tersimpan"), tr("Data telah diperbarui dengan sukses."));
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), qry.lastError().text());
    }

    conn.connClose();
}

//delete button
void input::on_pushButton_delete_clicked()
{
    login conn;
    QString Id, Name, Score1, Score2, Score3, Score4, Score5, Score6;
    Id = ui->txt_id->text();
    if (!conn.connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery qry;
    qry.prepare("Delete from Studentdata WHERE Id = :Id");
    qry.bindValue(":Id", Id);

    if (qry.exec())
    {
        QMessageBox::information(this, tr("Tersimpan"), tr("Data telah diperbarui dengan sukses."));
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), qry.lastError().text());
    }

    conn.connClose();
}


//sort by name

void input::on_pushButton_sortbyname_clicked()
{
    login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery qry(conn.mydb);

    qry.prepare("SELECT * FROM Studentdata ORDER BY Name ASC");

    if(qry.exec())
    {
        modal->setQuery(std::move(qry));
        ui->tableView->setModel(modal);
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), qry.lastError().text());
    }

    conn.connClose();
}

//sort by id

void input::on_pushButton_sortbyid_clicked()
{
    login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery qry(conn.mydb);

    qry.prepare("SELECT * FROM Studentdata ORDER BY Id ASC");

    if(qry.exec())
    {
        modal->setQuery(qry);
        ui->tableView->setModel(modal);
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), qry.lastError().text());
    }

    conn.connClose();
}

// ClearData


void input::on_pushButton_clear_clicked()
{
    login conn;
    conn.connOpen();

    if (!conn.connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery qry(conn.mydb);

    if (qry.exec("DELETE FROM Studentdata"))
    {
        QMessageBox::information(this, tr("Success"), tr("Data cleared successfully."));
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), qry.lastError().text());
    }

    conn.connClose();
}

//Next page
void input::on_pushButton_clicked()
{
    calculate thirdpage;
    thirdpage.setModal(true);
    thirdpage.exec();
}

