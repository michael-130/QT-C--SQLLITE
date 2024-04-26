#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
// ini  untuk memanggil file kedua
//
#include "input.h"
// disni untuk connect ke sql
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
//

QT_BEGIN_NAMESPACE
namespace Ui {
class login;
}
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;

    void connClose()
    {
        // Close the database connection
        mydb.close();

        // Remove the database connection
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen()
    {
        QSqlDatabase qdb;
        if(QSqlDatabase::contains("qt_sql_default_connection"))
            qdb = QSqlDatabase::database("qt_sql_default_connection");
        else
            qdb = QSqlDatabase::addDatabase("QSQLITE");
        // Set the database name
        qdb.setDatabaseName("C:/Qtproject/Database/database.db");

        // Open the database connection
        if (!qdb.open()){
            qDebug() << ("Failed to open the database");
            return false;
        }

        else{
            qDebug() << ("Connected....");
            return true;
        }
    }

public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_Github_clicked();

private:
    Ui::login *ui;

};
#endif // LOGIN_H
