#include "RobotState.h"
#include <QColor>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QQuickWindow>
#include <QSignalSpy>
#include <QTest>
#include <limits>

class RobotPanelTest : public QObject
{
    Q_OBJECT
private slots:
    void healthRules()
    {
        RobotState robot;
        QSignalSpy changed(&robot, &RobotState::healthChanged);
        QCOMPARE(robot.health(), 500);
        QCOMPARE(robot.maxHealth(), 500);
        robot.damage(0);
        robot.damage(-50);
        robot.damage(std::numeric_limits<int>::min());
        robot.reset();
        QCOMPARE(changed.count(), 0);
        robot.damage(50);
        QCOMPARE(robot.health(), 450);
        QCOMPARE(changed.count(), 1);
        robot.damage(std::numeric_limits<int>::max());
        QCOMPARE(robot.health(), 0);
        QCOMPARE(changed.count(), 2);
        robot.damage(50);
        QCOMPARE(changed.count(), 2);
        robot.reset();
        QCOMPARE(robot.health(), 500);
        QCOMPARE(changed.count(), 3);
    }

    void realWindowInteraction()
    {
        RobotState robot;
        QQmlApplicationEngine engine;
        QSignalSpy warnings(&engine, &QQmlEngine::warnings);
        engine.setInitialProperties({{"backend", QVariant::fromValue(&robot)}});
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
        QCOMPARE(engine.rootObjects().size(), 1);
        auto *window = qobject_cast<QQuickWindow *>(engine.rootObjects().first());
        QVERIFY(window);
        QVERIFY(QTest::qWaitForWindowExposed(window));

        QObject *panel = nullptr;
        for (auto *object : window->findChildren<QObject *>()) {
            if (object->metaObject()->indexOfProperty("damageButton") >= 0) {
                panel = object;
                break;
            }
        }
        QVERIFY(panel);
        auto *damage = panel->property("damageButton").value<QQuickItem *>();
        auto *reset = panel->property("resetButton").value<QQuickItem *>();
        QVERIFY(damage);
        QVERIFY(reset);
        QObject *healthText = nullptr;
        QObject *progress = nullptr;
        for (auto *object : panel->findChildren<QObject *>()) {
            if (object->property("text").toString().startsWith(QStringLiteral("血量：")))
                healthText = object;
            if (object->metaObject()->indexOfProperty("position") >= 0
                && object->metaObject()->indexOfProperty("to") >= 0)
                progress = object;
        }
        QVERIFY(healthText);
        QVERIFY(progress);
        const auto click = [window](QQuickItem *item) {
            QTest::mouseClick(window, Qt::LeftButton, Qt::NoModifier,
                item->mapToScene(QPointF(item->width() / 2, item->height() / 2)).toPoint());
        };
        QCOMPARE(panel->property("health").toInt(), 500);
        for (int n = 0; n < 8; ++n)
            click(damage);
        QTRY_COMPARE(robot.health(), 100);
        QTRY_COMPARE(panel->property("health").toInt(), 100);
        QTRY_COMPARE(healthText->property("text").toString(), QStringLiteral("血量：100 / 500"));
        QTRY_COMPARE(healthText->property("color").value<QColor>(), QColor("#ff8c7a"));
        QTRY_COMPARE(progress->property("value").toDouble(), 100.0);
        click(damage);
        click(damage);
        QTRY_COMPARE(robot.health(), 0);
        QTRY_VERIFY(!damage->isEnabled());
        click(damage);
        QCOMPARE(robot.health(), 0);
        click(reset);
        QTRY_COMPARE(robot.health(), 500);
        QTRY_VERIFY(damage->isEnabled());
        QTRY_COMPARE(progress->property("value").toDouble(), 500.0);
        QTRY_COMPARE(healthText->property("color").value<QColor>(), QColor("#d9e7f5"));

        window->resize(400, 300);
        QTest::qWait(100);
        for (auto *button : {damage, reset}) {
            const auto rect = button->mapRectToScene(button->boundingRect());
            QVERIFY(rect.width() > 0 && rect.height() > 0);
            QVERIFY(QRectF(0, 0, window->width(), window->height()).contains(rect));
        }
        click(damage);
        QTRY_COMPARE(robot.health(), 450);
        window->resize(900, 600);
        QTest::qWait(100);
        click(reset);
        QTRY_COMPARE(robot.health(), 500);
        QCOMPARE(warnings.count(), 0);
    }
};

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    RobotPanelTest test;
    return QTest::qExec(&test, argc, argv);
}
#include "robot_panel_test.moc"
