#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;
    w.show();
    a.setWindowIcon(QIcon("./images/icon.png"));
    return a.exec();

}
