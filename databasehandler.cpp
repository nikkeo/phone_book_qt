#include "databasehandler.h"
#include <QDebug>

DatabaseHandler::DatabaseHandler(const QString& dbName) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "Error: Couldn't open the database!";
    } else {
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS PhoneBook (Id INTEGER PRIMARY KEY, Name TEXT, PhoneNumber TEXT)");
    }
}

DatabaseHandler::~DatabaseHandler() {
    closeDatabase();
}

bool DatabaseHandler::openDatabase() {
    return db.open();
}

void DatabaseHandler::closeDatabase() {
    db.close();
}

std::vector<std::pair<QString, QString>> DatabaseHandler::getAllEntities() {
    std::vector<std::pair<QString, QString>> result;

    if (db.isOpen()) {
        QSqlQuery query("SELECT * FROM PhoneBook");

        while (query.next()) {
            QString name = query.value("Name").toString();
            QString phoneNumber = query.value("PhoneNumber").toString();

            result.emplace_back(name, phoneNumber);
        }

        emit entitiesFetched(result);
    }

    return result;
}

bool DatabaseHandler::isNameUnique(const QString& name) {
    if (db.isOpen()) {
        QSqlQuery query(db);
        query.prepare("SELECT Name FROM PhoneBook WHERE Name = :name");
        query.bindValue(":name", name);

        if (!query.exec()) {
            closeDatabase();
            return false;
        }

        bool isUnique = query.next();

        return !isUnique;
    }
    return false;
}

bool DatabaseHandler::addEntity(const QString& name, const QString& phoneNumber) {
    if (db.isOpen()) {
        if (!isNameUnique(name)) {
            qDebug() << "Name is not unique!";
            return false;
        }
        QSqlQuery query;
        query.prepare("INSERT INTO PhoneBook (Name, PhoneNumber) VALUES (:name, :phoneNumber)");
        query.bindValue(":name", name);
        query.bindValue(":phoneNumber", phoneNumber);

        return query.exec();
    }

    return false;
}

bool DatabaseHandler::deleteEntity(int entityId) {
    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("DELETE FROM PhoneBook WHERE Id = :id");
        query.bindValue(":id", entityId);

        return query.exec();
    }

    return false;
}

int DatabaseHandler::findEntityId(const QString& name) {
    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("SELECT Id FROM PhoneBook WHERE Name = :name");
        query.bindValue(":name", name);

        if (query.exec() && query.next()) {
            return query.value("Id").toInt();
        }
    }

    return -1;
}
