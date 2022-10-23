#include "database.h"

#include <QVariant>
#include <QDateTime>

bool db::Database::insertNewData(int temperature, int humidity, int pressure, double windSpeed)
{
    QSqlQuery query;
    query.prepare("INSERT INTO weather (temperature, humidity, pressure, wind_speed, time)"
               "VALUES (:temperature, :humidity, :pressure, :wind_speed, :time)");
    query.bindValue(":temperature", temperature);
    query.bindValue(":humidity", humidity);
    query.bindValue(":pressure", pressure);
    query.bindValue(":wind_speed", windSpeed);
    query.bindValue(":time", QDateTime::currentDateTime().toString());

    return query.exec();
}

db::WeatherModel db::Database::getWeatherModel(QString time)
{

}

db::Database::Database() {
    dbPath = "weather.db";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    db.open();
}

db::Database::~Database()
{
    db.close();
}
