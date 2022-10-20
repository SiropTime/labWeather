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

void WeatherData::getData()
{
    QNetworkRequest request(formFinalUrl());

    networkManager->get(request);

    connect(networkManager, &QNetworkAccessManager::finished, [&](QNetworkReply *reply) {
        QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();
        currentWeatherStatus =  jsonObject.value("weather")[0]["main"].toString();
        currentDegrees = (int) jsonObject.value("main")["temp"].toDouble() - 273;

        emit weatherChanged("currentWeatherStatus");
        emit degreesChanged("currentDegrees");
        qDebug() << currentWeatherStatus << currentDegrees;
    });

}

QUrl WeatherData::formFinalUrl()
{
    QUrl rUrl(url);
    QUrlQuery query;
    query.addQueryItem("lat", QString::number(latitude));
    query.addQueryItem("lon", QString::number(longitude));
    query.addQueryItem("appid", apiKey);

    rUrl.setQuery(query.query());

    return rUrl;
}

