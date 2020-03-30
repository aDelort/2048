#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "counter.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    Counter scoreCounter;
    Counter bestScoreCounter;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("vueObjetScoreCnt", &scoreCounter);
    engine.rootContext()->setContextProperty("vueObjetBestScoreCnt", &bestScoreCounter);
    engine.load(url);

    return app.exec();
}
