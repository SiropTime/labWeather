#include "weatherdata.h"

WeatherData::WeatherData()
{

    qDebug() << longitude << latitude;

    networkManager = new QNetworkAccessManager(this);

    getData();
}

QString WeatherData::getCurrentWeatherStatus()
{
    return currentWeatherStatus;
}

int WeatherData::getCurrentDegrees()
{
    return currentDegrees;
}

double WeatherData::getCurrentWindSpeed()
{
    return currentWindSpeed;
}

QString WeatherData::getCurrentWindDirection()
{
    return currentWindDirection;
}

int WeatherData::getCurrentHumidity()
{
    return currentHumidity;
}

QString WeatherData::getWeatherImagePath()
{
    return weatherImagePath;
}

void WeatherData::changeLocation(double lat, double lon)
{
    latitude = lat;
    longitude = lon;
}

void WeatherData::update()
{
    QNetworkRequest request(formFinalUrl());
    networkManager->get(request);
}

void WeatherData::getData()
{
    QNetworkRequest request(formFinalUrl());

    networkManager->get(request);

    connect(networkManager, &QNetworkAccessManager::finished, [&](QNetworkReply *reply) {
        QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();
        currentWeatherStatus =  jsonObject.value("weather")[0]["description"].toString();
        currentWeatherStatus[0] = currentWeatherStatus[0].toUpper();
        currentDegrees = static_cast<int>((jsonObject.value("main")["temp"].toDouble() - 272.1) + 0.5); // Adding half to round correctly -_-

        makeDirectionFromDegrees(jsonObject.value("wind")["deg"].toInt());
        currentWindSpeed = jsonObject.value("wind")["speed"].toDouble();

        currentHumidity = jsonObject.value("main")["humidity"].toInt();

        makeSignal();

        qDebug() << jsonObject;
    });

}

void WeatherData::makeSignal()
{

    emit weatherChanged("currentWeatherStatus");
    emit degreesChanged("currentDegrees");
    emit windSpeedChanged("currentWindSpeed");
    emit windDirectionChanged("currentWindDirection");
    emit humidityChanged("currentHumidity");
    emit weatherImageChanged("weatherImagePath");
}

QUrl WeatherData::formFinalUrl()
{
    QUrl rUrl(url);
    QUrlQuery query;
    query.addQueryItem("lat", QString::number(latitude));
    query.addQueryItem("lon", QString::number(longitude));
    query.addQueryItem("appid", apiKey);
    query.addQueryItem("lang", "ru");

    rUrl.setQuery(query.query());

    return rUrl;
}

QString WeatherData::makeDirectionFromDegrees(int windDegrees)
{
    QString returnString;

    if ((windDegrees > 337 && windDegrees < 360) || (windDegrees > 0 && windDegrees < 24)) {
        returnString = "Север";
    } else if (windDegrees > 293 && windDegrees < 338) {
        returnString = "Северо-Запад";
    } else if (windDegrees > 247 && windDegrees < 294) {
        returnString = "Запад";
    } else if (windDegrees > 203 && windDegrees < 248) {
        returnString = "Юго-Запад";
    } else if (windDegrees > 157 && windDegrees < 204) {
        returnString = "Юг";
    } else if (windDegrees > 113 && windDegrees < 158) {
        returnString = "Юго-Восток";
    } else if (windDegrees > 67 && windDegrees < 114) {
        returnString = "Восток";
    } else if (windDegrees > 23 && windDegrees < 68) {
        returnString = "Северо-Восток";
    }

    currentWindDirection = returnString;
    return returnString;
}

