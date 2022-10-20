#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QSslSocket>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QQmlContext>


#include "weatherdata.h"

int main(int argc, char *argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQuickView view;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QQmlContext* ctx = engine.rootContext();
    WeatherData wd;

    ctx->setContextProperty("weatherData", &wd);

    return app.exec();
}
