// mainwindow.cpp
#include "mainapp.h"
#include "ui_mainapp.h"
#include <QMessageBox>

MainApp::MainApp(DatabaseHandler *dbHandler, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainApp) {
    ui->setupUi(this);

    databaseHandler = dbHandler;
    dbHandler->openDatabase();

    connect(databaseHandler, &DatabaseHandler::entitiesFetched, this, &MainApp::onDataFetchComplete);
}

MainApp::~MainApp() {
    delete ui;
}

void MainApp::on_addButton_clicked() {
    QString name = ui->nameLineEdit->text();
    QString phoneNumber = ui->phoneNumberLineEdit->text();

    if (name.isEmpty() || phoneNumber.isEmpty()) {
        QMessageBox::warning(this, "Error", "Name and phone number cannot be empty");
        return;
    }

    if (databaseHandler->addEntity(name, phoneNumber)) {
        ui->nameLineEdit->clear();
        ui->phoneNumberLineEdit->clear();
    }
}

void MainApp::on_deleteButton_clicked() {
    int entityId = databaseHandler->findEntityId(ui->deleteByName->text());

    if (entityId <= 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid ID");
        return;
    }

    if (databaseHandler->deleteEntity(entityId)) {
        ui->deleteByName->clear();
    }
}

void MainApp::on_viewAllButton_clicked() {
    databaseHandler->getAllEntities();
}

void MainApp::onDataAdded() {
    QMessageBox::information(this, "Success", "Data added successfully");
}

void MainApp::onDataDeleted() {
    QMessageBox::information(this, "Success", "Data deleted successfully");
}

void MainApp::onDataFetchComplete(const std::vector<std::pair<QString, QString>>& entities) {
    ui->textBrowser->clear();

    for (const auto &item : entities) {
        const QString& name = item.first;
        const QString& phoneNumber = item.second;

        if (!phoneNumber.isEmpty()) {
            ui->textBrowser->append("Name: " + name + ", Phone Number: " + phoneNumber);
        } else {
            ui->textBrowser->append("Name: " + name + ", Phone Number: [No Number]");
        }
    }
}
