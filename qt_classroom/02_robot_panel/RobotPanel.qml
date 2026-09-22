import QtQuick

RobotPanelForm {
    id: panel
    required property var backend
    health: panel.backend.health
    maxHealth: panel.backend.maxHealth

    Connections {
        target: panel.damageButton
        function onClicked() {
            panel.backend.damage(50);
        }
    }
    Connections {
        target: panel.resetButton
        function onClicked() {
            panel.backend.reset();
        }
    }
}
