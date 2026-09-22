#include "RobotState.h"
#include <algorithm>

RobotState::RobotState(QObject *parent) : QObject(parent) {}

int RobotState::health() const
{
    return m_health;
}

int RobotState::maxHealth() const
{
    return 500;
}

void RobotState::damage(int amount)
{
    if (amount <= 0)
        return;
    setHealth(m_health - std::min(amount, m_health));
}

void RobotState::reset()
{
    setHealth(maxHealth());
}

void RobotState::setHealth(int value)
{
    const int next = std::clamp(value, 0, maxHealth());
    if (m_health == next)
        return;
    m_health = next;
    emit healthChanged();
}
