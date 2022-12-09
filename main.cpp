#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include "appengine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QQmlComponent component(&engine, url);
    QObject *object = component.create();

    AppEngine appEngine(object);
    engine.rootContext()->setContextProperty("appEngine", &appEngine);

    return app.exec();
}
