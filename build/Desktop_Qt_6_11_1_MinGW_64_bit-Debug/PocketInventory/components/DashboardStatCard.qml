import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    property string title: ""
    property int value: 0
    property string unit: ""
    property color accentColor: "#2563EB"

    AppTheme {
        id: theme
    }

    implicitHeight: 125

    radius: theme.radiusLarge
    color: theme.surface

    border.width: 1
    border.color: theme.border

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 18

        spacing: 8

        Label {
            text: root.title

            color: theme.textSecondary
            font.pixelSize: 13
        }

        RowLayout {
            spacing: 4

            Label {
                text: root.value

                color: theme.textPrimary

                font.pixelSize: 28
                font.bold: true
            }

            Label {
                text: root.unit

                color: theme.textSecondary
                font.pixelSize: 14

                Layout.alignment: Qt.AlignBottom
            }

            Item {
                Layout.fillWidth: true
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 3

            radius: 2
            color: root.accentColor
        }
    }
}