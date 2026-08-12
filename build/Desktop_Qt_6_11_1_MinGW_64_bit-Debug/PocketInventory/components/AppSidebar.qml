import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    property int currentPage: 0

    signal pageRequested(int pageIndex)

    AppTheme {
        id: theme
    }

    implicitWidth: theme.sidebarWidth

    color: theme.sidebar

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16

        spacing: 8

        // =========================
        // Logo
        // =========================

        ColumnLayout {
            Layout.fillWidth: true
            Layout.bottomMargin: 24

            spacing: 1

            Label {
                text: "Pocket"

                color: "white"

                font.pixelSize: 19
                font.bold: true
            }

            Label {
                text: "INVENTORY"

                color: "#64748B"

                font.pixelSize: 10
                font.letterSpacing: 2
            }
        }

        // =========================
        // Navigation
        // =========================

        NavButton {
            text: "대시보드"

            selected:
                root.currentPage === 0

            onClicked: {
                root.pageRequested(0)
            }
        }

        NavButton {
            text: "재고 관리"

            selected:
                root.currentPage === 1

            onClicked: {
                root.pageRequested(1)
            }
        }

        NavButton {
            text: "변경 이력"

            selected:
                root.currentPage === 2

            onClicked: {
                root.pageRequested(2)
            }
        }

        Item {
            Layout.fillHeight: true
        }

        // =========================
        // Footer
        // =========================

        ColumnLayout {
            Layout.fillWidth: true

            spacing: 2

            Label {
                text: "PocketInventory"

                color: "#9CA3AF"

                font.pixelSize: 11
            }

            Label {
                text: "v0.1"

                color: "#6B7280"

                font.pixelSize: 10
            }
        }
    }
}