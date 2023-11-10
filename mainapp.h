#ifndef MAINAPP_H
#define MAINAPP_H

#include <QMainWindow>
#include "databasehandler.h"

namespace Ui {
class MainApp;
}

class MainApp : public QMainWindow {
    Q_OBJECT

public:
    explicit MainApp(DatabaseHandler *dbHandler, QWidget *parent = nullptr);
    ~MainApp();

private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_viewAllButton_clicked();
    void onDataAdded();
    void onDataDeleted();
    void onDataFetchComplete(const std::vector<std::pair<QString, QString>>& data);

private:
    Ui::MainApp *ui;
    DatabaseHandler *databaseHandler;
};

#endif // MAINAPP_H
