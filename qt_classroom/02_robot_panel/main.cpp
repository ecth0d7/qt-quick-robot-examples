#include "RobotState.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QUrl>
#include <QVariant>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    RobotState robot; // 先创建后端，保证它比 QML 引擎更晚销毁。
    QQmlApplicationEngine engine;
    engine.setInitialProperties({{"backend", QVariant::fromValue(&robot)}});
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return 1;
    return app.exec();
}
