#include "mainwindow.h"
#include <QLabel>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CToDoList app;
    app.show();

    return a.exec();
}






