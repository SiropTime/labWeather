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

#define uint8 unsigned char

const uint8 SUNNY = 0;
const uint8 RAIN = 1;
const uint8 CLOUDY = 2;
const uint8 PARTLY_CLOUDY = 3;
const uint8 STORM = 4;
const uint8 SNOW = 5;

class WeatherData : public QObject
{
    Q_OBJECT
public:
    WeatherData();
//    explicit WeatherData(QObject *parent = nullptr);
    uint8 getCurrentWeatherStatus();
    int getCurrentDegrees();

private:
    uint8 currentWeatherStatus = SUNNY;
    int currentDegrees = 2;
    double latitude = 55.753192;
    double longitude = 37.622443;

    const QString url = "https://api.openweathermap.org/data/2.5/weather";
    const QString apiKey = "e0051abe21f6d9196e19a4308b44c329";

    QNetworkAccessManager* networkManager;

    void getData();

    QUrl formFinalUrl();


signals:

public slots:
    void slotFinished();
};

#endif // WEATHERDATA_H
