import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    required property string category
    required property int productCount
    required property int totalQuantity
    required property int lowStockCount
    required property var inventoryValue

    AppTheme {
        id: theme
    }

    implicitHeight: 46

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10

        Label {
            Layout.preferredWidth: 200

            text: root.category

            font.pixelSize: 13
            font.bold: true

            color: theme.textPrimary
        }

        Label {
            Layout.preferredWidth: 120

            text: root.productCount + "종"

            font.pixelSize: 13
            color: theme.textPrimary

            horizontalAlignment: Text.AlignRight
        }

        Label {
            Layout.preferredWidth: 120

            text: Number(root.totalQuantity).toLocaleString(Qt.locale("ko_KR")) + "개"

            font.pixelSize: 13
            color: theme.textPrimary

            horizontalAlignment: Text.AlignRight
        }

        Label {
            Layout.preferredWidth: 120

            text: root.lowStockCount + "개"

            font.pixelSize: 13
            font.bold: root.lowStockCount > 0

            color: root.lowStockCount > 0 ? theme.danger : theme.textSecondary

            horizontalAlignment: Text.AlignRight
        }

        Label {
            Layout.fillWidth: true

            text: Number(root.inventoryValue).toLocaleString(Qt.locale("ko_KR"), "f", 0) + "원"

            font.pixelSize: 13
            font.bold: true

            color: theme.primary

            horizontalAlignment: Text.AlignRight
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