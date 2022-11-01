#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include <QString>
#include <QObject>
#include <QVariantList>
#include <QDateTime>

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
            this->time = QDateTime::currentDateTime().toString();
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
//    std::vector<WeatherModel> weatherModels;s
    QString dbPath;
    QSqlDatabase db;

public slots:
    bool insertNewData(int temperature, int humidity, int pressure, double windSpeed);
    Q_INVOKABLE QVariantList getDataForChart();
};

}

#endif // DATABASE_H
