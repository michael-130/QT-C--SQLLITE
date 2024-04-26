#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "input.h"
#include <QDesktopServices>

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    QPixmap pix("C:/Qtproject/png/OIP.jpeg");
    ui->label_picture->setPixmap(pix);
    // sampai sini
    if (!connOpen())//panggil yang di login page.h

        ui->Status_label->setText("Failed to open the database");

    else
        ui->Status_label->setText("Connected....");

}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    QString username, password;
    username = ui->lineedit_username->text();
    password = ui->lineEdit_password->text();

    if (!connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }

    connOpen(); // Open the database connection

    QSqlQuery qry;
    qry.prepare("SELECT * FROM Studentdata WHERE username = :username AND password = :password");
    qry.bindValue(":username", username);
    qry.bindValue(":password", password);

    if (qry.exec())
    {
        int count = 0; // Declare and initialize count

        while (qry.next())
        {
            count++;
        }

        if (count == 1)
        {
            ui->Status_label_2->setText("Username and password are correct");
            // If username and password are correct
            // Close the connection from the first login screen
            // And proceed to the second page with database connection
            connClose();
            this->hide();
            input Input;
            Input.setModal(true);
            Input.exec();
        }
        else if (count > 1)
        {
            ui->Status_label_2->setText("Duplicate Username and password");
        }
        else // count < 1
        {
            ui->Status_label_2->setText(" Username and password not correct");
        }
    }
    else
    {
        qDebug() << "Query execution failed";
    }
}

void login::on_pushButton_Github_clicked()
{
     QDesktopServices::openUrl(QUrl("https://github.com/"));
}

