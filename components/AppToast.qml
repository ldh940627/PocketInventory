import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    property string messageText: ""

    width:
        Math.min(
            contentRow.implicitWidth + 32,
            380
        )

    height: 46

    radius: 10

    visible: false

    color: "#1F2937"

    border.width: 1
    border.color: "#374151"

    RowLayout {
        id: contentRow

        anchors.fill: parent
        anchors.leftMargin: 14
        anchors.rightMargin: 14

        spacing: 10

        Rectangle {
            id: indicator

            width: 7
            height: 7
            radius: 4

            color: "#9CA3AF"
        }

        Label {
            text: root.messageText

            color: "white"

            font.pixelSize: 12

            Layout.fillWidth: true
        }
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
            indicator.color = "#E5484D"
            break

        case "green":
            indicator.color = "#16A66A"
            break

        case "darkorange":
            indicator.color = "#E79A24"
            break

        default:
            indicator.color = "#4F6EF7"
            break
        }

        root.visible = true
        hideTimer.restart()
    }
}