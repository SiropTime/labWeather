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
    Q_PROPERTY(QString weatherImagePath READ getWeatherImagePath NOTIFY weatherImageChanged)
    Q_PROPERTY(int currentDegrees READ getCurrentDegrees NOTIFY degreesChanged)
    Q_PROPERTY(double currentWindSpeed READ getCurrentWindSpeed NOTIFY windSpeedChanged)
    Q_PROPERTY(QString currentWindDirection READ getCurrentWindDirection NOTIFY windDirectionChanged)
    Q_PROPERTY(int currentHumidity READ getCurrentHumidity NOTIFY humidityChanged)

public:
    WeatherData();

    QString getCurrentWeatherStatus();
    int getCurrentDegrees();
    double getCurrentWindSpeed();
    QString getCurrentWindDirection();
    int getCurrentHumidity();
    QString getWeatherImagePath();

    void changeLocation(double lat, double lon);
    void update();


private:
    QString currentWeatherStatus = "Clear";
    int currentDegrees = 2;
    double currentWindSpeed = 0.62;
    QString currentWindDirection = "Север";
    int currentHumidity = 80;

    QString weatherImagePath = "clouds";

    double latitude = 55.753192;
    double longitude = 37.622443;

    const QString url = "https://api.openweathermap.org/data/2.5/weather";
    const QString apiKey = "e0051abe21f6d9196e19a4308b44c329";

    QNetworkAccessManager* networkManager;

    void makeSignal();
    void getData();
    QUrl formFinalUrl();
    QString makeDirectionFromDegrees(int windDegrees);

    enum weatherStatuses {
        clear,
        clouds,
        rain
    };

// Telling QT
signals:
    void weatherChanged(QString data);
    void degreesChanged(QString data);
    void windSpeedChanged(QString data);
    void windDirectionChanged(QString data);
    void humidityChanged(QString data);
    void weatherImageChanged(QString data);
};

#endif // WEATHERDATA_H
