#include "weatherdata.h"

WeatherData::WeatherData()
{

    qDebug() << longitude << latitude;

    networkManager = new QNetworkAccessManager(this);

    getData();
}

//WeatherData::WeatherData(QObject *parent) : QObject{parent}
//{
//    getData();
//}

unsigned char WeatherData::getCurrentWeatherStatus()
{
    return currentWeatherStatus;
}

int WeatherData::getCurrentDegrees()
{
    return currentDegrees;
}

void WeatherData::getData()
{
    qDebug() << formFinalUrl();

    QNetworkRequest request(formFinalUrl());


    qDebug() << "en";
    qDebug() << formFinalUrl();

    networkManager->get(request);

    connect(networkManager, &QNetworkAccessManager::finished, [&](QNetworkReply *reply) {
        qDebug() << QString::fromStdString(reply->readAll().toStdString());
        QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();
        qDebug() << jsonObject["weather"].toString();
    });

    qDebug() << "en";


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

void WeatherData::slotFinished()
{

}
