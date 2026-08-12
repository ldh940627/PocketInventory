import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    required property string productName
    required property int productQuantity
    required property int minimumQuantity

    AppTheme {
        id: theme
    }

    implicitHeight: 56
    color: "transparent"

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 4
        anchors.rightMargin: 4

        spacing: 12

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 2

            Label {
                text: root.productName

                color: theme.textPrimary

                font.pixelSize: 14
                font.bold: true
            }

            Label {
                text:
                    "최소 재고 "
                    + root.minimumQuantity
                    + "개"

                color: theme.textSecondary
                font.pixelSize: 12
            }
        }

        Rectangle {
            implicitWidth: 72
            implicitHeight: 28

            radius: 14

            color: theme.dangerSoft

            Label {
                anchors.centerIn: parent

                text:
                    root.productQuantity
                    + "개"

                color: theme.danger

                font.bold: true
            }
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        height: 1

        color: theme.border
    }
}