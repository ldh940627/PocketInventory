import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Button {
    id: root

    property bool selected: false

    Layout.fillWidth: true

    implicitHeight: 46

    hoverEnabled: true

    leftPadding: 0
    rightPadding: 0

    background: Rectangle {
        radius: 8

        color:
            root.selected
            ? "#1E293B"
            : root.hovered
                ? "#1B2433"
                : "transparent"

        Rectangle {
            visible: root.selected

            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter

            width: 3
            height: 24

            radius: 2

            color: "#4F6EF7"
        }
    }

    contentItem: RowLayout {
        spacing: 0

        Item {
            Layout.preferredWidth: 16
        }

        Label {
            text: root.text

            color:
                root.selected
                ? "white"
                : "#CBD5E1"

            font.pixelSize: 14
            font.bold: root.selected

            Layout.fillWidth: true
        }
    }
}