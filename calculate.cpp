#include "calculate.h"
#include "ui_calculate.h"
#include "input.h"
#include "login.h"
#include "output.h"

calculate::calculate(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::calculate)
{
    ui->setupUi(this);
    QPixmap pix("C:/Qtproject/png/R.jpeg");
    ui->label_picture->setPixmap(pix);
}

calculate::~calculate()
{
    delete ui;
}
//calculate total score average score student
void calculate::on_button_total_avg_score_clicked()
{
    login conn;
    if (!conn.connOpen()) {
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery qry;
    qry.prepare("SELECT Id, Name, \"Score 1\", \"Score 2\", \"Score 3\", \"Score 4\", \"Score 5\", \"Score 6\", "
                "(\"Score 1\" + \"Score 2\" + \"Score 3\" + \"Score 4\" + \"Score 5\" + \"Score 6\") AS TotalScore, "
                "((\"Score 1\" + \"Score 2\" + \"Score 3\" + \"Score 4\" + \"Score 5\" + \"Score 6\") / 6.0) AS AverageScore "
                "FROM Studentdata");

    if (!qry.exec()) {
        qDebug() << "Error executing query:" << qry.lastError().text();
        conn.connClose();
        return;
    }

    ui->tableWidget->clear(); // Clear previous content of the table widget

    // Set column headers
    QStringList headers;
    headers << "ID" << "Name" << "Score 1" << "Score 2" << "Score 3" << "Score 4" << "Score 5" << "Score 6" << "Total Score" << "Average Score";
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Populate the table with query results
    int row = 0;
    while (qry.next()) {
        ui->tableWidget->insertRow(row);
        for (int column = 0; column < 10; ++column) { // 10 columns including ID, Name, Score 1-6, Total Score, and Average Score
            QTableWidgetItem *item = new QTableWidgetItem(qry.value(column).toString());
            ui->tableWidget->setItem(row, column, item);
        }
        ++row;
    }

    conn.connClose();

    // Enable the button to update total score and average score
    ui->pushButton_Updatedata->setEnabled(true);
}

void calculate::on_pushButton_Updatedata_clicked()
{
    login conn;
    if (!conn.connOpen()) {
        qDebug() << "Failed to open the database";
        return;
    }

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QString id = ui->tableWidget->item(row, 0)->text();
        QString score1 = ui->tableWidget->item(row, 2)->text();
        QString score2 = ui->tableWidget->item(row, 3)->text();
        QString score3 = ui->tableWidget->item(row, 4)->text();
        QString score4 = ui->tableWidget->item(row, 5)->text();
        QString score5 = ui->tableWidget->item(row, 6)->text();
        QString score6 = ui->tableWidget->item(row, 7)->text();

        // Calculate total score for the current row
        int totalScore = score1.toInt() + score2.toInt() + score3.toInt() + score4.toInt() + score5.toInt() + score6.toInt();
        // Calculate average score for the current row
        double averageScore = totalScore / 6.0;

        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE Studentdata SET \"Score 1\" = :score1, "
                            "\"Score 2\" = :score2, "
                            "\"Score 3\" = :score3, "
                            "\"Score 4\" = :score4, "
                            "\"Score 5\" = :score5, "
                            "\"Score 6\" = :score6, "
                            "\"Total Score\" = :totalScore, "
                            "\"Average Score\" = :averageScore "
                            "WHERE Id = :id");
        updateQuery.bindValue(":score1", score1);
        updateQuery.bindValue(":score2", score2);
        updateQuery.bindValue(":score3", score3);
        updateQuery.bindValue(":score4", score4);
        updateQuery.bindValue(":score5", score5);
        updateQuery.bindValue(":score6", score6);
        updateQuery.bindValue(":totalScore", totalScore);
        updateQuery.bindValue(":averageScore", averageScore);
        updateQuery.bindValue(":id", id);

        if (!updateQuery.exec()) {
            qDebug() << "Error executing update query:" << updateQuery.lastError().text();
            conn.connClose();
            return;
        }
    }

    conn.connClose();
}



//calculate every course
void calculate::on_pushButton_calc_2_clicked()
{
    login conn;
    if (!conn.connOpen()) {
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery qry;
    qry.prepare("SELECT Course, "
                "SUM(\"Score 1\") AS Total_Score_1, "
                "SUM(\"Score 2\") AS Total_Score_2, "
                "SUM(\"Score 3\") AS Total_Score_3, "
                "SUM(\"Score 4\") AS Total_Score_4, "
                "SUM(\"Score 5\") AS Total_Score_5, "
                "SUM(\"Score 6\") AS Total_Score_6, "
                "AVG(\"Score 1\") AS Average_Score_1, "
                "AVG(\"Score 2\") AS Average_Score_2, "
                "AVG(\"Score 3\") AS Average_Score_3, "
                "AVG(\"Score 4\") AS Average_Score_4, "
                "AVG(\"Score 5\") AS Average_Score_5, "
                "AVG(\"Score 6\") AS Average_Score_6 "
                "FROM Studentdata "
                "GROUP BY Course");

    if (!qry.exec()) {
        qDebug() << "Error executing query:" << qry.lastError().text();
        conn.connClose();
        return;
    }

    ui->tableWidget->clear(); // Clear previous content of the table widget

    // Set column headers
    QStringList headers;
    headers << "Course" << "Total Score 1" << "Total Score 2" << "Total Score 3" << "Total Score 4" << "Total Score 5" << "Total Score 6"
            << "Average Score 1" << "Average Score 2" << "Average Score 3" << "Average Score 4" << "Average Score 5" << "Average Score 6";
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Populate the table with query results
    int row = 0;
    while (qry.next()) {
        ui->tableWidget->insertRow(row);
        for (int column = 0; column < headers.size(); ++column) {
            QTableWidgetItem *item = new QTableWidgetItem(qry.value(column).toString());
            ui->tableWidget->setItem(row, column, item);
        }
        ++row;
    }

    conn.connClose();
}

// desencding total score
void calculate::on_pushButton_clicked()
{

    login conn;
    if (!conn.connOpen()) {
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery qry;
    qry.prepare("SELECT Id, Name, "
                "SUM(\"Score 1\" + \"Score 2\" + \"Score 3\" + \"Score 4\" + \"Score 5\" + \"Score 6\") AS Total_Score "
                "FROM Studentdata "
                "GROUP BY Id, Name "
                "ORDER BY Total_Score DESC"); // Sort in descending order by Total_Score

    if (!qry.exec()) {
        qDebug() << "Error executing query:" << qry.lastError().text();
        conn.connClose();
        return;
    }

    ui->tableWidget->clear(); // Clear previous content of the table widget

    // Set column headers
    QStringList headers;
    headers << "ID" << "Name" << "Total Score";
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Populate the table with query results
    int row = 0;
    while (qry.next()) {
        ui->tableWidget->insertRow(row);
        for (int column = 0; column < headers.size(); ++column) {
            QTableWidgetItem *item = new QTableWidgetItem(qry.value(column).toString());
            ui->tableWidget->setItem(row, column, item);
        }
        ++row;
    }

    conn.connClose();
}

//ascending total score
void calculate::on_pushButton_2_clicked()
{
    login conn;
    if (!conn.connOpen()) {
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery qry;
    qry.prepare("SELECT Id, Name, "
                "SUM(\"Score 1\" + \"Score 2\" + \"Score 3\" + \"Score 4\" + \"Score 5\" + \"Score 6\") AS Total_Score "
                "FROM Studentdata "
                "GROUP BY Id, Name "
                "ORDER BY Total_Score ASC"); // Sort in ascending order by Total_Score

    if (!qry.exec()) {
        qDebug() << "Error executing query:" << qry.lastError().text();
        conn.connClose();
        return;
    }

    ui->tableWidget->clear(); // Clear previous content of the table widget

    // Set column headers
    QStringList headers;
    headers << "ID" << "Name" << "Total Score";
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Populate the table with query results
    int row = 0;
    while (qry.next()) {
        ui->tableWidget->insertRow(row);
        for (int column = 0; column < headers.size(); ++column) {
            QTableWidgetItem *item = new QTableWidgetItem(qry.value(column).toString());
            ui->tableWidget->setItem(row, column, item);
        }
        ++row;
    }

    conn.connClose();
}


void calculate::on_pushButton_3_clicked()
{
    login conn;
    if (!conn.connOpen()) {
        qDebug() << "Failed to open the database";
        return;
    }

    QString searchText = ui->lineEdit_search->text().trimmed(); // Get the search text from the line edit
    bool isNumeric = searchText.toInt(); // Check if the search text is numeric

    QSqlQuery qry;
    if (isNumeric) {
        // Search by student ID
        qry.prepare("SELECT Id, Name, \"Score 1\", \"Score 2\", \"Score 3\", \"Score 4\", \"Score 5\", \"Score 6\", "
                    "\"Total Score\", \"Average Score\" "
                    "FROM Studentdata "
                    "WHERE Id = :searchText");
    } else {
        // Search by total score
        qry.prepare("SELECT Id, Name, \"Score 1\", \"Score 2\", \"Score 3\", \"Score 4\", \"Score 5\", \"Score 6\", "
                    "\"Total Score\", \"Average Score\" "
                    "FROM Studentdata "
                    "WHERE \"Total Score\" = :searchText");
    }

    qry.bindValue(":searchText", searchText);

    if (!qry.exec()) {
        qDebug() << "Error executing query:" << qry.lastError().text();
        conn.connClose();
        return;
    }

    ui->tableWidget->clear(); // Clear previous content of the table widget

    // Set column headers
    QStringList headers;
    headers << "ID" << "Name" << "Score 1" << "Score 2" << "Score 3" << "Score 4" << "Score 5" << "Score 6" << "Total Score" << "Average Score";
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Populate the table with query results
    int row = 0;
    while (qry.next()) {
        ui->tableWidget->insertRow(row);
        for (int column = 0; column < headers.size(); ++column) {
            QTableWidgetItem *item = new QTableWidgetItem(qry.value(column).toString());
            ui->tableWidget->setItem(row, column, item);
        }
        ++row;
    }

    conn.connClose();
}

// there is an error
void calculate::on_pushButton_4_clicked() {
    login conn;
    if (!conn.connOpen()) {
        qDebug() << "Gagal membuka basis data";
        return;
    }

    QString searchText = ui->lineEdit_search->text().trimmed(); // Dapatkan teks pencarian dari line edit

    QSqlQuery qry;
    qry.prepare("SELECT Id, Name, \"Score 1\", \"Score 2\", \"Score 3\", \"Score 4\", \"Score 5\", \"Score 6\", "
                "\"Total Score\", \"Average Score\" "
                "FROM Studentdata "
                "WHERE Name LIKE :searchText");

    // Add wildcards to search for partial matches
    qry.bindValue(":searchText", "%" + searchText + "%");

    if (!qry.exec()) {
        qDebug() << "Error executing query:" << qry.lastError().text();
        conn.connClose();
        return;
    }

    ui->tableWidget->clear(); // Hapus konten sebelumnya dari widget tabel

    // Set header kolom
    QStringList headers;
    headers << "ID" << "Name" << "Score 1" << "Score 2" << "Score 3" << "Score 4" << "Score 5" << "Score 6" << "Total Score" << "Average Score";
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Ambil satu baris pertama yang sesuai dari hasil kueri
    int row = 0;
    while (qry.next()) {
        ui->tableWidget->insertRow(row);
        for (int column = 0; column < headers.size(); ++column) {
            QTableWidgetItem *item = new QTableWidgetItem(qry.value(column).toString());
            ui->tableWidget->setItem(row, column, item);
        }
        ++row;
    }
    conn.connClose();
}






//statistic analysis


void calculate::addRowToTable(const QString &grade, int count, int totalStudents, int row)
{
    QTableWidgetItem *gradeItem = new QTableWidgetItem(grade);
    QTableWidgetItem *countItem = new QTableWidgetItem(QString::number(count));
    double percentage = (count / static_cast<double>(totalStudents)) * 100.0;
    QTableWidgetItem *percentageItem;
    if (qIsFinite(percentage)) {
        percentageItem = new QTableWidgetItem(QString::number(percentage, 'f', 2) + "%");
    } else {
        percentageItem = new QTableWidgetItem("0.00%");
    }

    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, gradeItem);
    ui->tableWidget->setItem(row, 1, countItem);
    ui->tableWidget->setItem(row, 2, percentageItem);
}
void calculate::on_pushButton_5_statisc_clicked() {
    login conn;
    if (!conn.connOpen()) {
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery qry;
    // Count the number of students in each grade category
    qry.prepare("SELECT "
                "SUM(CASE WHEN \"Average Score\" BETWEEN 90 AND 100 THEN 1 ELSE 0 END) AS ExcellentCount, "
                "SUM(CASE WHEN \"Average Score\" BETWEEN 80 AND 89 THEN 1 ELSE 0 END) AS GoodCount, "
                "SUM(CASE WHEN \"Average Score\" BETWEEN 70 AND 79 THEN 1 ELSE 0 END) AS AverageCount, "
                "SUM(CASE WHEN \"Average Score\" BETWEEN 60 AND 69 THEN 1 ELSE 0 END) AS PassCount, "
                "SUM(CASE WHEN \"Average Score\" BETWEEN 0 AND 59 THEN 1 ELSE 0 END) AS FailCount "
                "FROM Studentdata");

    if (!qry.exec()) {
        qDebug() << "Error executing query:" << qry.lastError().text();
        conn.connClose();
        return;
    }

    // Calculate total number of students
    int totalStudents = 0;
    while (qry.next()) {
        totalStudents += qry.value(0).toInt() + qry.value(1).toInt() + qry.value(2).toInt() + qry.value(3).toInt() + qry.value(4).toInt();
    }

    // Clear previous content of the table widget
    ui->tableWidget->clear();

    // Set column headers
    QStringList headers;
    headers << "Grade" << "Count" << "Percentage";
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Populate the table with query results
    int row = 0;
    qry.first(); // Move back to the first record
    do {
        addRowToTable("Excellent", qry.value(0).toInt(), totalStudents, row++);
        addRowToTable("Good", qry.value(1).toInt(), totalStudents, row++);
        addRowToTable("Average", qry.value(2).toInt(), totalStudents, row++);
        addRowToTable("Pass", qry.value(3).toInt(), totalStudents, row++);
        addRowToTable("Fail", qry.value(4).toInt(), totalStudents, row++);
    } while (qry.next());

    conn.connClose();
}


void calculate::on_pushButton_nextpage_2_clicked()
{
    //Next page
    output fourthpage;
    fourthpage.setModal(true);
    fourthpage.exec();

}

