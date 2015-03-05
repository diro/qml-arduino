#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include "arduinomgr.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQuickView *view = new QQuickView;
    ArduinoMgr arduino(0);
    view->engine()->rootContext()->setContextProperty("arduino", &arduino);

    view->setSource(QStringLiteral("qrc:/arduino.qml"));
    view->show();

    return app.exec();
}
