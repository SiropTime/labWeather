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
    int temperature;
    int humidity;
    int pressure;
    double windSpeed;
    QString time;

    WeatherModel(int temperature, int humidity, int pressure, double windSpeed, QString time = "now") {
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
    explicit Database(QObject *parent = 0);
    ~Database();
    void close();

    WeatherModel getWeatherModel(QString time);
    std::vector<WeatherModel> getAllModels();

private:
    void createDatabase();
    std::map<QString, WeatherModel> weatherModels;
    QString dbPath;
    QSqlDatabase db;

public slots:
    bool insertNewData(int temperature, int humidity, int pressure, double windSpeed);
};

}

#endif // DATABASE_H
