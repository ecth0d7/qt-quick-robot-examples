import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 480
    height: 300
    visible: true
    title: "Hello Qt"
    color: "#101b2a"

    Label {
        anchors.centerIn: parent
        text: "Hello RoboMaster!"
        color: "white"
        font.pixelSize: 28
    }
}
