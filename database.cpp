#include "database.h"

#include <QVariant>
#include <QDebug>
#include <QDir>
#include <QSqlError>
#include <QSqlRecord>

bool db::Database::insertNewData(int temperature, int humidity, int pressure, double windSpeed)
{
    QSqlQuery query(db.database());

    query.prepare("INSERT INTO weather (temperature, humidity, pressure, wind_speed, time)"
               "VALUES (:temperature, :humidity, :pressure, :wind_speed, :time);");
    query.bindValue(":temperature", temperature);
    query.bindValue(":humidity", humidity);
    query.bindValue(":pressure", pressure);
    query.bindValue(":wind_speed", windSpeed);
    query.bindValue(":time", QDateTime::currentDateTime().toString());

    bool success = query.exec();
    if (!success) {
        qWarning() << "INSERTION ERROR: " << query.lastError();
    } else {
        qDebug() << "Successfully added information in DB";
    }
    return success;
}

db::WeatherModel db::Database::getWeatherModel(QString time)
{
    return WeatherModel(6,82, 1000, 2.3, "now");
}

std::vector<db::WeatherModel> db::Database::getAllModels()
{
    std::vector<db::WeatherModel> allWeatherModels;
    QSqlQuery query(db.database());

    query.prepare("SELECT * FROM weather;");
    if (query.exec()) {
        QSqlRecord record = query.record();

        // Preparing indexes for getting them from query
        const int temperatureIndex = record.indexOf("temperature");
        const int humidityIndex = record.indexOf("humidity");
        const int pressureIndex = record.indexOf("pressure");
        const int windSpeedIndex = record.indexOf("wind_speed");
        const int timeIndex = record.indexOf("time");

        while (query.next()) {
            auto tempWeatherModel = db::WeatherModel(query.value(temperatureIndex).toInt(), query.value(humidityIndex).toInt(),
                                                     query.value(pressureIndex).toInt(), query.value(windSpeedIndex).toDouble(), query.value(timeIndex).toString());
            allWeatherModels.push_back(tempWeatherModel);
        }
    } else {
        qWarning() << "SELECT ERROR: can't make request";
    }

    return allWeatherModels;
}

QVariantList db::Database::getDataForChart()
{
    QVariantList returnValues;
    std::vector<db::WeatherModel> models = getAllModels();
    for (auto const model : models) {
        returnValues.append((QDateTime::fromString(model.time).toSecsSinceEpoch() - 1667174400) / 60);
        returnValues.append(model.temperature);
    }

    return returnValues;
}

void db::Database::createDatabase()
{
    QDir databasePath;
    qDebug() << "We're in db constructor";
    dbPath = databasePath.currentPath() + "/weather.db";
    qDebug() << dbPath;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("weather");
    db.setDatabaseName(dbPath);
    bool result = db.open();

    if (!result) {
        qWarning() << "OPENING TABLE ERROR!";
    } else {
        qDebug() << "Succesfully opened DB";
    }

    QSqlQuery query;
    result = query.exec("CREATE TABLE IF NOT EXISTS weather ("
               "temperature INT          NOT NULL,"
               "humidity    INT          NOT NULL,"
               "pressure    INT          NOT NULL,"
               "wind_speed  DOUBLE       NOT NULL,"
               "time        VARCHAR (50) NOT NULL UNIQUE PRIMARY KEY);" );
    if (!result) {
        qWarning() << "CREATING TABLE ERROR: " << query.lastError();
    } else {
        qDebug() << "Created table successfully!";
    }
}

db::Database::Database()
{
    createDatabase();
}

db::Database::Database(QObject *parent) : QObject(parent)
{
    createDatabase();
}

db::Database::~Database()
{
    db.close();
}

void db::Database::close()
{
    db.close();
}
