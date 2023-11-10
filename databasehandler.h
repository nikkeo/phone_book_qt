#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <vector>

class DatabaseHandler : public QObject {
    Q_OBJECT

private:
    QSqlDatabase db;

public:
    DatabaseHandler(const QString& dbName);
    ~DatabaseHandler();

    bool openDatabase();
    void closeDatabase();

    signals:
        void entitiesFetched(const std::vector<std::pair<QString, QString>>& entities);


public slots:
    std::vector<std::pair<QString, QString>> getAllEntities();

    bool addEntity(const QString& name, const QString& phoneNumber);
    bool deleteEntity(int entityId);
    int findEntityId(const QString& name);
    bool isNameUnique(const QString& name);
};

#endif // DATABASEHANDLER_H
