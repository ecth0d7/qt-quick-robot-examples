#pragma once

#include <QObject>

class RobotState final : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int health READ health NOTIFY healthChanged)
    Q_PROPERTY(int maxHealth READ maxHealth CONSTANT)

public:
    explicit RobotState(QObject *parent = nullptr);

    int health() const;
    int maxHealth() const;
    Q_INVOKABLE void damage(int amount);
    Q_INVOKABLE void reset();

signals:
    void healthChanged();

private:
    void setHealth(int value);
    int m_health = 500;
};
