#include "weatherdata.h"

//WeatherData::WeatherData(QObject *parent) : QObject(parent)
//{
//    networkManager = new QNetworkAccessManager(this);
//    dataBase = new db::Database(this);
//    getData();
//}

WeatherData::~WeatherData()
{

}

WeatherData::WeatherData()
{

    qDebug() << longitude << latitude;

    networkManager = new QNetworkAccessManager(this);
    dataBase = new db::Database(this);
    getData();
}

void WeatherData::exit()
{
    dataBase->close();
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

double WeatherData::getCurrentPressure()
{
    return currentPressure;
}

db::Database *WeatherData::getDataBase()
{
    return dataBase;
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

        qDebug() << jsonObject;

        currentWeatherStatus =  jsonObject.value("weather")[0]["description"].toString();
        currentWeatherStatus[0] = currentWeatherStatus[0].toUpper();
        currentDegrees = static_cast<int>((jsonObject.value("main")["temp"].toDouble() - 272.1) + 0.5); // Kelvins to Celsium

        makeDirectionFromDegrees(jsonObject.value("wind")["deg"].toInt());
        currentWindSpeed = jsonObject.value("wind")["speed"].toDouble();

        currentHumidity = jsonObject.value("main")["humidity"].toInt();
        currentPressure = jsonObject.value("main")["pressure"].toInt() * 0.7501; // hPa to mm ртутного столба (не знаю, как на инглише)

        auto weatherImage = jsonObject.value("weather")[0]["icon"].toString();
        setWeatherImage(jsonObject.value("weather")[0]["main"].toString(),
                // There's d or n in icon for day and night inc icon value ("04d" f.e.)
               weatherImage.at(weatherImage.size() - 1) == "n" ? true : false);

        // Inserting data in database but something broken in this
        dataBase->insertNewData(currentDegrees, currentHumidity, currentPressure, currentWindSpeed);
//        dataBase->getAllModels();

        makeSignal(); // Notifying QT that we changed some fields that are used in GUI


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
    emit pressureChanged("currentPressure");
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

void WeatherData::setWeatherImage(QString weather, bool isNight)
{

    if (weather == "Rain" || weather == "Drizzle") {
        weatherImagePath = !isNight ? "rain" : "night_rain";
    } else if (weather == "Clouds") {
        weatherImagePath = !isNight ? "clouds" : "night_clouds";
    } else if (weather == "Thunderstorm") {
        weatherImagePath = "storm";
    } else if (weather == "Clear") {
        weatherImagePath = !isNight ? "clear" : "night_clear";
    } else if (weather == "Snow") {
        weatherImagePath = "snow";
    } else {
        weatherImagePath = "fog";
    }


}

