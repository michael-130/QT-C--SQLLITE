#include "output.h"
#include "ui_output.h"
#include "login.h"
#include <QAxObject>
#include <QFileDialog>
#include <QMessageBox> // Include header for QMessageBox
#include <QFile>
#include <QTextStream>
#include <QMediaPlayer>
#include <QUrl>
output::output(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::output)
{
    ui->setupUi(this);
    QPixmap pix("C:/Qtproject/png/R.jpeg");
    ui->label_picture->setPixmap(pix);
}

output::~output()
{
    delete ui;
}


void output::on_pushButton_READ_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Buka File"), QDir::homePath(), tr("File Teks (*.txt);;Semua file (*)"));
    if (filePath.isEmpty())
        return;
    // Open the text file
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Gagal membuka file untuk pembacaan:" << file.errorString();
        QMessageBox::critical(this, tr("Error"), tr("Gagal membuka file untuk pembacaan: %1").arg(file.errorString()));
        return;
    }
    // Clear the existing contents of the table widget
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0); // Reset row count

    // Read the contents of the text file and populate the table widget
    QTextStream in(&file);
    int row = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts); // Split based on one or more spaces

        // Add a new row
        ui->tableWidget->insertRow(row);

        // Populate the columns in the current row
        for (int col = 0; col < parts.size(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(parts[col]);
            ui->tableWidget->setItem(row, col, item);
        }

        row++;
    }

    file.close();
}

//List Record
void output::on_pushButton_loadtable_clicked()
{
    login conn;

    if (!conn.connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    qry->prepare("SELECT * FROM Studentdata");

    if (qry->exec())
    {
        // Clear previous content of the table widget
        ui->tableWidget->clear();

        // Set column headers
        QStringList headers;
        headers << "ID" << "Name" << "Score 1" << "Score 2" << "Score 3" << "Score 4" << "Score 5" << "Score 6" << "Total Score" << "Average Score";
        ui->tableWidget->setColumnCount(headers.size());
        ui->tableWidget->setHorizontalHeaderLabels(headers);

        // Populate the table widget with query results
        int row = 0;
        while (qry->next()) {
            ui->tableWidget->insertRow(row);
            for (int column = 0; column < headers.size(); ++column) {
                QTableWidgetItem *item = new QTableWidgetItem(qry->value(column).toString());
                ui->tableWidget->setItem(row, column, item);
            }
            ++row;
        }
    }
    else
    {
        qDebug() << "Failed to execute query";
    }

    conn.connClose();
}

// write to txt file
void output::on_pushButtonwrite_clicked()
{
    // Selecting the file path for saving the text file
    QString fileName = QFileDialog::getSaveFileName(this, tr("Simpan File"), QDir::homePath() + "/Desktop/output.txt", tr("File Teks (*.txt)"));

    // Check if the user canceled file selection or provided an empty file name
    if (fileName.isEmpty())
        return; // Exit the function if the file name is empty or the user canceled

    // Membuka koneksi ke database
    login conn;
    if (!conn.connOpen()) {
        qDebug() << "Gagal membuka koneksi ke database";
        return;
    }

    // Membuat objek QSqlQuery dan mengeksekusi query untuk mengambil data dari tabel Studentdata
    QSqlQuery qry(conn.mydb);
    if (!qry.exec("SELECT * FROM Studentdata")) {
        qDebug() << "Gagal menjalankan query:" << qry.lastError().text();
        conn.connClose(); // Tutup koneksi karena query gagal
        return;
    }

    // Membuka file untuk penulisan teks
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Gagal membuka file untuk penulisan";
        conn.connClose(); // Tutup koneksi karena gagal membuka file
        return;
    }

    QTextStream out(&file);

    // Menulis isi tabel ke file teks
    while (qry.next()) {
        for (int column = 0; column < qry.record().count(); ++column) {
            out << qry.value(column).toString() << "\t"; // Gunakan tab sebagai pemisah
        }
        out << "\n"; // Akhir baris
    }

    file.close();

    // Pesan debug bahwa data berhasil ditulis ke file
    qDebug() << "Data berhasil ditulis ke file" << fileName;

    // Tutup koneksi setelah selesai
    conn.connClose();
}




//write to csv

void output::on_pushButtonwrite_2_clicked()
{
    // Selecting the file path for saving the CSV file
    QString fileName = QFileDialog::getSaveFileName(this, tr("Simpan File"), QDir::homePath() + "/Desktop/output.csv", tr("File CSV (*.csv)"));

    // Check if the user canceled file selection or provided an empty file name
    if (fileName.isEmpty())
        return; // Exit the function if the file name is empty or the user canceled

    // Membuka koneksi ke database
    login conn;
    if (!conn.connOpen()) {
        qDebug() << "Gagal membuka koneksi ke database";
        return;
    }

    // Membuat objek QSqlQuery dan mengeksekusi query untuk mengambil data dari tabel Studentdata
    QSqlQuery qry(conn.mydb);
    if (!qry.exec("SELECT * FROM Studentdata")) {
        qDebug() << "Gagal menjalankan query:" << qry.lastError().text();
        conn.connClose(); // Tutup koneksi karena query gagal
        return;
    }

    // Membuka file untuk penulisan teks
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Gagal membuka file untuk penulisan";
        conn.connClose(); // Tutup koneksi karena gagal membuka file
        return;
    }

    QTextStream out(&file);

    // Menulis isi tabel ke file CSV
    while (qry.next()) {
        for (int column = 0; column < qry.record().count(); ++column) {
            out << "\"" << qry.value(column).toString() << "\""; // Gunakan tanda kutip untuk menghindari masalah dengan nilai yang mengandung koma
            if (column < qry.record().count() - 1)
                out << ","; // Pemisah kolom CSV
        }
        out << "\n"; // Akhir baris
    }

    file.close();

    // Pesan debug bahwa data berhasil ditulis ke file
    qDebug() << "Data berhasil ditulis ke file" << fileName;

    // Tutup koneksi setelah selesai
    conn.connClose();
}


