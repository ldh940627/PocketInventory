import QtQuick
import QtQuick.Controls

Rectangle {
    id: root

    property string messageText: ""

    width:
        Math.min(
            messageLabel.implicitWidth + 40,
            500
        )

    height: 44

    radius: 8

    visible: false

    color: "#111827"
    opacity: 0.95

    Label {
        id: messageLabel

        anchors.centerIn: parent

        text: root.messageText

        color: "white"
        font.pixelSize: 13
    }

    Timer {
        id: hideTimer

        interval: 2500

        onTriggered: {
            root.visible = false
        }
    }

    function show(message, colorName) {
        root.messageText = message

        switch (colorName) {
        case "red":
            root.color = "#DC2626"
            break

        case "green":
            root.color = "#16A34A"
            break

        case "darkorange":
            root.color = "#D97706"
            break

        default:
            root.color = "#374151"
            break
        }

        root.visible = true
        hideTimer.restart()
    }
}