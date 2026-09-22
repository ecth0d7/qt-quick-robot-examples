import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: window
    required property var backend
    width: 560
    height: 340
    minimumWidth: 400
    minimumHeight: 300
    visible: true
    title: "机器人状态面板"
    color: "#101b2a"

    RobotPanel {
        anchors.fill: parent
        anchors.margins: 24
        backend: window.backend
    }
}
