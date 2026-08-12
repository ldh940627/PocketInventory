import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    default property alias content:
        contentArea.data

    property string title: ""

    AppTheme {
        id: theme
    }

    radius: theme.radiusLarge

    color: theme.surface

    border.width: 1
    border.color: theme.border

    ColumnLayout {
        anchors.fill: parent

        spacing: 0

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 58

            Label {
                anchors.left: parent.left
                anchors.leftMargin: 18
                anchors.verticalCenter:
                    parent.verticalCenter

                text: root.title

                color: theme.textPrimary

                font.pixelSize: 16
                font.bold: true
            }

            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                height: 1

                color: theme.border
            }
        }

        Item {
            id: contentArea

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}