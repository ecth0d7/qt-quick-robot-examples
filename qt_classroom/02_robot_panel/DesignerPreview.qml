import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 560
    height: 340
    visible: true
    title: "设计预览：静态示例数据"
    color: "#101b2a"

    RobotPanelForm {
        anchors.fill: parent
        anchors.margins: 24
        health: 350
        maxHealth: 500
    }
}
