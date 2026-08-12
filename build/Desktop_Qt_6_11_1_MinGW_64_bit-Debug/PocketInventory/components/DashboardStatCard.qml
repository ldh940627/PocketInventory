import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    property string title: ""
    property string valueText: "0"
    property string unit: ""

    property color accentColor: "#4F6EF7"

    AppTheme {
        id: theme
    }

    implicitHeight: 118

    radius: theme.radiusLarge

    color: theme.surface

    border.width: 1
    border.color: theme.border

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 18

        spacing: 8

        // =========================
        // Title
        // =========================

        Label {
            text: root.title

            color: theme.textSecondary

            font.pixelSize: 12
        }

        // =========================
        // Value
        // =========================

        RowLayout {
            Layout.fillWidth: true

            spacing: 4

            Label {
                text: root.valueText

                color: theme.textPrimary

                font.pixelSize: 26
                font.bold: true
            }

            Label {
                text: root.unit

                visible:
                    root.unit !== ""

                color: theme.textSecondary

                font.pixelSize: 12

                Layout.alignment:
                    Qt.AlignBottom
            }

            Item {
                Layout.fillWidth: true
            }
        }

        Item {
            Layout.fillHeight: true
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 3

            radius: 2

            color: root.accentColor
        }
    }
}