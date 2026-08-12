import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "components"
import "Pages"

ApplicationWindow {
    id: rootWindow

    required property var inventoryViewModel
    required property var historyViewModel

    width: 1280
    height: 800

    minimumWidth: 1000
    minimumHeight: 650

    visible: true

    title: qsTr("PocketInventory")

    color: theme.background

    property int currentPage: 0

    AppTheme {
        id: theme
    }

    Connections {
        target: rootWindow.inventoryViewModel

        function onMessageRequested(message, colorName) {
            toastMessage.show(
                message,
                colorName
            )
        }
    }

    RowLayout {
        anchors.fill: parent

        spacing: 0

        AppSidebar {
            Layout.preferredWidth:
                theme.sidebarWidth

            Layout.fillHeight: true

            currentPage:
                rootWindow.currentPage

            onPageRequested: function(pageIndex) {
                rootWindow.currentPage = pageIndex
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true

            color: theme.background

            ColumnLayout {
                anchors.fill: parent

                spacing: 0

                AppHeader {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 60
                }

                StackLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    currentIndex:
                        rootWindow.currentPage

                    DashboardPage {
                        inventoryViewModel:
                            rootWindow.inventoryViewModel

                        historyViewModel:
                            rootWindow.historyViewModel
                    }

                    InventoryPage {
                        inventoryViewModel:
                            rootWindow.inventoryViewModel
                    }

                    HistoryPage {
                        historyViewModel:
                            rootWindow.historyViewModel
                    }
                }
            }
        }
    }

    AppToast {
        id: toastMessage

        anchors.horizontalCenter:
            parent.horizontalCenter

        anchors.top:
            parent.top

        anchors.topMargin: 72

        z: 1000
    }
}