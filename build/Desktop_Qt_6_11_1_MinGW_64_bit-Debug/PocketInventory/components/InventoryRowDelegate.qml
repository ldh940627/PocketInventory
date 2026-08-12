import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    required property int index
    required property string productName
    required property int productQuantity
    required property int minimumQuantity

    signal actionRequested(int proxyIndex)

    AppTheme {
        id: theme
    }

    implicitHeight: 62

    color:
        mouseArea.containsMouse
        ? theme.surfaceSoft
        : "transparent"

    RowLayout {
        anchors.fill: parent

        anchors.leftMargin: 20
        anchors.rightMargin: 20

        spacing: 12

        Label {
            text: root.productName

            Layout.fillWidth: true
            Layout.preferredWidth: 4

            color: theme.textPrimary

            font.pixelSize: 14
            font.bold: true
        }

        Label {
            text:
                root.productQuantity + "개"

            Layout.preferredWidth: 90

            color: theme.textPrimary

            font.pixelSize: 14
            font.bold: true
        }

        Label {
            text:
                root.minimumQuantity + "개"

            Layout.preferredWidth: 90

            color: theme.textSecondary

            font.pixelSize: 13
        }

        RowLayout {
            Layout.preferredWidth: 90

            spacing: 6

            Rectangle {
                width: 7
                height: 7

                radius: 4

                color:
                    root.productQuantity
                        <= root.minimumQuantity
                    ? theme.danger
                    : theme.success
            }

            Label {
                text:
                    root.productQuantity
                        <= root.minimumQuantity
                    ? "부족"
                    : "정상"

                color:
                    root.productQuantity
                        <= root.minimumQuantity
                    ? theme.danger
                    : theme.success

                font.pixelSize: 12
                font.bold: true
            }
        }

        Button {
            id: actionButton

            Layout.preferredWidth: 36
            Layout.preferredHeight: 34

            text: "⋮"

            onClicked: {
                root.actionRequested(
                    root.index
                )
            }

            contentItem: Text {
                text: actionButton.text

                font.pixelSize: 20

                color: theme.textSecondary

                horizontalAlignment:
                    Text.AlignHCenter

                verticalAlignment:
                    Text.AlignVCenter
            }

            background: Rectangle {
                radius: 7

                color:
                    actionButton.hovered
                    ? "#F1F3F6"
                    : "transparent"
            }
        }
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent

        hoverEnabled: true

        acceptedButtons:
            Qt.NoButton
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        height: 1

        color: theme.border
    }
}