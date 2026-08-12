import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "../components"

Item {
    id: root

    required property var inventoryViewModel
    required property var historyViewModel

    AppTheme {
        id: theme
    }

    ScrollView {
        anchors.fill: parent
        clip: true

        contentWidth: availableWidth

        Item {
            width: parent.width

            implicitHeight:
                pageContainer.implicitHeight

            Item {
                id: pageContainer

                anchors.top: parent.top
                anchors.horizontalCenter:
                    parent.horizontalCenter

                width:
                    Math.min(
                        parent.width - 56,
                        1180
                    )

                implicitHeight:
                    contentContainer.implicitHeight + 56

                ColumnLayout {
                    id: contentContainer

                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top

                    anchors.topMargin: 28

                    spacing: theme.sectionSpacing

                    // =========================
                    // Header
                    // =========================

                    ColumnLayout {
                        Layout.fillWidth: true

                        spacing: 3

                        Label {
                            text: "대시보드"

                            font.pixelSize: 28
                            font.bold: true

                            color: theme.textPrimary
                        }

                        Label {
                            text:
                                "현재 재고 상태와 최근 변경 사항을 한눈에 확인하세요."

                            font.pixelSize: 13

                            color: theme.textSecondary
                        }
                    }

                    // =========================
                    // KPI
                    // =========================

                    RowLayout {
                        Layout.fillWidth: true

                        spacing: 14

                        DashboardStatCard {
                            Layout.fillWidth: true
                            Layout.preferredWidth: 1

                            title: "전체 상품"

                            value:
                                root.inventoryViewModel.totalCount

                            unit: "개"

                            accentColor: theme.primary
                        }

                        DashboardStatCard {
                            Layout.fillWidth: true
                            Layout.preferredWidth: 1

                            title: "정상 재고"

                            value:
                                root.inventoryViewModel.normalStockCount

                            unit: "개"

                            accentColor: theme.success
                        }

                        DashboardStatCard {
                            Layout.fillWidth: true
                            Layout.preferredWidth: 1

                            title: "부족 재고"

                            value:
                                root.inventoryViewModel.lowStockCount

                            unit: "개"

                            accentColor: theme.danger
                        }

                        DashboardStatCard {
                            Layout.fillWidth: true
                            Layout.preferredWidth: 1

                            title: "재고 변경"

                            value:
                                root.historyViewModel.totalCount

                            unit: "건"

                            accentColor: theme.warning
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        Layout.topMargin: 4

                        Label {
                            text: "주의가 필요한 재고"

                            font.pixelSize: 16
                            font.bold: true

                            color: theme.textPrimary
                        }

                        Item {
                            Layout.fillWidth: true
                        }

                        Label {
                            text:
                                root.inventoryViewModel.lowStockCount
                                + "개 부족"

                            visible:
                                root.inventoryViewModel.lowStockCount > 0

                            color: theme.danger

                            font.pixelSize: 12
                            font.bold: true
                        }
                    }

                    // =========================
                    // Panels
                    // =========================

                    RowLayout {
                        Layout.fillWidth: true

                        spacing: 14

                        DashboardPanel {
                            Layout.fillWidth: true
                            Layout.preferredWidth: 1
                            Layout.preferredHeight: 340

                            title: "부족 재고"

                            Item {
                                anchors.fill: parent

                                ListView {
                                    id: lowStockList

                                    anchors.fill: parent

                                    anchors.leftMargin: 14
                                    anchors.rightMargin: 14
                                    anchors.topMargin: 6
                                    anchors.bottomMargin: 6

                                    clip: true

                                    model:
                                        root.inventoryViewModel.lowStockProducts

                                    delegate:
                                        LowStockDashboardDelegate {
                                            width: lowStockList.width
                                        }
                                }

                                Label {
                                    anchors.centerIn: parent

                                    visible:
                                        root.inventoryViewModel.lowStockCount === 0

                                    text:
                                        "현재 부족 재고가 없습니다."

                                    color: theme.textSecondary
                                }
                            }
                        }

                        DashboardPanel {
                            Layout.fillWidth: true
                            Layout.preferredWidth: 1
                            Layout.preferredHeight: 340

                            title: "최근 재고 변경"

                            Item {
                                anchors.fill: parent

                                ListView {
                                    id: recentHistoryList

                                    anchors.fill: parent

                                    anchors.leftMargin: 14
                                    anchors.rightMargin: 14
                                    anchors.topMargin: 6
                                    anchors.bottomMargin: 6

                                    clip: true

                                    model:
                                        root.historyViewModel.recentHistory

                                    delegate:
                                        RecentHistoryDelegate {
                                            id: recentDelegate

                                            width:
                                                recentHistoryList.width

                                            visible:
                                                recentDelegate.index < 5

                                            height:
                                                recentDelegate.index < 5
                                                ? implicitHeight
                                                : 0
                                        }
                                }

                                Label {
                                    anchors.centerIn: parent

                                    visible:
                                        root.historyViewModel.totalCount === 0

                                    text:
                                        "재고 변경 이력이 없습니다."

                                    color:
                                        theme.textSecondary
                                }
                            }
                        }
                    }

                    Item {
                        Layout.preferredHeight: 20
                    }
                }
            }
        }
    }
}