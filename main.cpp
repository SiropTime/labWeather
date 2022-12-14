#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QSslSocket>
#include <QtQml/QQmlEngine>
#include <QQmlContext>
#include <QIcon>
#include <QTimer>
#include <QObject>

#include "weatherdata.h"

int main(int argc, char *argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    WeatherData wd;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    QIcon windowIcon(":/img/clear.ico");
    app.setWindowIcon(windowIcon);
    QQmlContext* ctx = engine.rootContext();

    ctx->setContextProperty("weatherData", &wd);
    ctx->setContextProperty("dataBase", wd.getDataBase());

    // Updating data every ten minutes
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        wd.update();
    });
    timer.start(600000);

    wd.exit();

    return app.exec();
}
