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

class WeatherData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentWeatherStatus READ getCurrentWeatherStatus NOTIFY weatherChanged)
    Q_PROPERTY(int currentDegrees READ getCurrentDegrees NOTIFY degreesChanged)
public:
    WeatherData();
//    explicit WeatherData(QObject *parent = nullptr);
    QString getCurrentWeatherStatus();
    int getCurrentDegrees();

private:
    QString currentWeatherStatus;
    int currentDegrees = 2;

    double latitude = 55.753192;
    double longitude = 37.622443;

    const QString url = "https://api.openweathermap.org/data/2.5/weather";
    const QString apiKey = "e0051abe21f6d9196e19a4308b44c329";

    QNetworkAccessManager* networkManager;

    void getData();

    QUrl formFinalUrl();


signals:
    void weatherChanged(QString data);
    void degreesChanged(QString data);
};

#endif // WEATHERDATA_H
