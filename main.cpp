#include "mainapp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseHandler dbHandler("my_phonebook.sqlite");
    MainApp mainApp(&dbHandler);
    mainApp.show();
    return a.exec();
}
