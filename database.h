#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include <QString>
#include <QObject>

#include <vector>
#include <map>

namespace db {



class WeatherModel {
public:
    int id;
    int temperature;
    int humidity;
    int pressure;
    double windSpeed;
    QString time;

    WeatherModel(int id, int temperature, int humidity, int pressure, double windSpeed, QString time = "now") {
        this->id = id;
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        this->windSpeed = windSpeed;
        if (time == "now") {

        } else {
            this->time = time;
        }

    }

};

class Database : public QObject {

    Q_OBJECT

public:
    Database();
    ~Database();

    bool insertNewData(int temperature, int humidity, int pressure, double windSpeed);
    WeatherModel getWeatherModel(QString time);
    std::vector<WeatherModel> getAllModels();

private:
    std::map<QString, WeatherModel> weatherModels;
    QString dbPath;
    QSqlDatabase db;
};

}

#endif // DATABASE_H
