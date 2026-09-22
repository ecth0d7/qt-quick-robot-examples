import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    width: 512
    height: 292
    radius: 12
    color: "#1c3046"

    property int health: 500
    property int maxHealth: 500
    property alias damageButton: damageButton
    property alias resetButton: resetButton

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 16

        Label {
            text: "RED 1 · 步兵"
            color: "white"
            font.pixelSize: 24
        }
        Label {
            text: "血量：" + root.health + " / " + root.maxHealth
            color: root.health < 150 ? "#ff8c7a" : "#d9e7f5"
            font.pixelSize: 20
        }
        ProgressBar {
            Layout.fillWidth: true
            from: 0
            to: root.maxHealth
            value: root.health
        }
        RowLayout {
            Button {
                id: damageButton
                text: "模拟受击 -50"
                enabled: root.health > 0
            }
            Button {
                id: resetButton
                text: "恢复"
            }
        }
        Item {
            Layout.fillHeight: true
        }
    }
}
