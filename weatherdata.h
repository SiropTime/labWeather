#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <iostream>

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QString>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtSql/QSqlQuery>

#include "database.h"


class WeatherData : public QObject
{
    Q_OBJECT

    // Fields that will be used in GUI. Setting field, method that returns it (getter) and signal method
    Q_PROPERTY(QString currentWeatherStatus READ getCurrentWeatherStatus NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherImagePath READ getWeatherImagePath NOTIFY weatherImageChanged)
    Q_PROPERTY(int currentDegrees READ getCurrentDegrees NOTIFY degreesChanged)
    Q_PROPERTY(double currentWindSpeed READ getCurrentWindSpeed NOTIFY windSpeedChanged)
    Q_PROPERTY(QString currentWindDirection READ getCurrentWindDirection NOTIFY windDirectionChanged)
    Q_PROPERTY(int currentHumidity READ getCurrentHumidity NOTIFY humidityChanged)
    Q_PROPERTY(double currentPressure READ getCurrentPressure NOTIFY pressureChanged)

public:
//    explicit WeatherData(QObject *parent = 0);
    WeatherData();
    ~WeatherData();

    void exit();
    /*
     Actually in real development we don't need so much getters but for making signals there it is
    */
    QString getCurrentWeatherStatus();
    int getCurrentDegrees();
    double getCurrentWindSpeed();
    QString getCurrentWindDirection();
    int getCurrentHumidity();
    QString getWeatherImagePath();
    double getCurrentPressure();

    void changeLocation(double lat, double lon);
    void update(); // Sending get request to update information


private:
    QString currentWeatherStatus = "Ясно";
    int currentDegrees = 2;
    double currentWindSpeed = 0.62;
    QString currentWindDirection = "Север";
    int currentHumidity = 80;
    double currentPressure = 761.31;

    QString weatherImagePath = "clouds";

    double latitude = 55.753192;
    double longitude = 37.622443;

    const QString url = "https://api.openweathermap.org/data/2.5/weather";
    const QString apiKey = "e0051abe21f6d9196e19a4308b44c329";

    QNetworkAccessManager* networkManager;
    db::Database* dataBase;

    void makeSignal();
    void getData(); // Setuping get request and initializing everything first time
    QUrl formFinalUrl(); // Forming query, adding key and returning need url
    QString makeDirectionFromDegrees(int windDegrees); // Converting degrees in response to normal string direction to show in GUI
    void setWeatherImage(QString weather, bool isNight); // Changing main weather image

// Telling QT that some fields are updated
signals:
    void weatherChanged(QString data);
    void degreesChanged(QString data);
    void windSpeedChanged(QString data);
    void windDirectionChanged(QString data);
    void humidityChanged(QString data);
    void weatherImageChanged(QString data);
    void pressureChanged(QString data);
};

#endif // WEATHERDATA_H
