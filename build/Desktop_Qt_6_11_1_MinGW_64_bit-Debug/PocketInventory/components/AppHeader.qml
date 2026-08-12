import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    AppTheme {
        id: theme
    }

    implicitHeight: 60

    color: theme.surface

    RowLayout {
        anchors.fill: parent

        anchors.leftMargin: 28
        anchors.rightMargin: 28

        Label {
            text: "PocketInventory"

            color: theme.textSecondary
            font.pixelSize: 13
        }

        Item {
            Layout.fillWidth: true
        }

        Label {
            text:
                Qt.formatDate(
                    new Date(),
                    "yyyy.MM.dd"
                )

            color: theme.textMuted
            font.pixelSize: 12
        }
    }

    Rectangle {
        anchors.bottom: parent.bottom

        width: parent.width
        height: 1

        color: theme.border
    }
}