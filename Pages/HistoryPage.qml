import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "../components"

Item {
    id: root

    required property var historyViewModel

    AppTheme {
        id: theme
    }

    Item {
        id: contentContainer

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        width: Math.min(
            parent.width - 56,
            1180
        )

        ColumnLayout {
            anchors.fill: parent

            anchors.topMargin: 28
            anchors.bottomMargin: 28

            spacing: theme.sectionSpacing

            // ====================================================
            // Header
            // ====================================================

            ColumnLayout {
                Layout.fillWidth: true

                spacing: 3

                Label {
                    text: "변경 이력"

                    font.pixelSize: 28
                    font.bold: true

                    color: theme.textPrimary
                }

                Label {
                    text: "재고 변동 기록을 확인합니다."

                    font.pixelSize: 13

                    color: theme.textSecondary
                }
            }

            // ====================================================
            // Filter
            // ====================================================

            HistoryFilterBar {
                Layout.fillWidth: true

                historyViewModel:
                    root.historyViewModel
            }

            // ====================================================
            // Result Count
            // ====================================================

            RowLayout {
                Layout.fillWidth: true

                Label {
                    text:
                        "이력 "
                        + root.historyViewModel.count
                        + "건"

                    color: theme.textSecondary

                    font.pixelSize: 12
                    font.bold: true
                }

                Item {
                    Layout.fillWidth: true
                }
            }

            // ====================================================
            // History Table
            // ====================================================

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true

                radius: theme.radiusLarge

                color: theme.surface

                border.width: 1
                border.color: theme.border

                clip: true

                ColumnLayout {
                    anchors.fill: parent

                    spacing: 0

                    // ============================================
                    // Table Header
                    // ============================================

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 48

                        color: theme.surfaceSoft

                        RowLayout {
                            anchors.fill: parent

                            anchors.leftMargin: 20
                            anchors.rightMargin: 20

                            spacing: 16

                            Label {
                                text: "상품"

                                Layout.fillWidth: true
                                Layout.preferredWidth: 4

                                font.pixelSize: 12
                                font.bold: true

                                color: theme.textSecondary
                            }

                            Label {
                                text: "변경"

                                Layout.preferredWidth: 170

                                font.pixelSize: 12
                                font.bold: true

                                color: theme.textSecondary

                                horizontalAlignment: Text.AlignHCenter
                            }

                            Label {
                                text: "유형"

                                Layout.preferredWidth: 110

                                font.pixelSize: 12
                                font.bold: true

                                color: theme.textSecondary

                                horizontalAlignment: Text.AlignHCenter
                            }

                            Label {
                                text: "일시"

                                Layout.preferredWidth: 130

                                font.pixelSize: 12
                                font.bold: true

                                color: theme.textSecondary

                                horizontalAlignment: Text.AlignHCenter
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

                    // ============================================
                    // History List
                    // ============================================

                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        ListView {
                            id: historyListView

                            anchors.fill: parent

                            clip: true

                            model:
                                root.historyViewModel.history

                            spacing: 0

                            delegate: HistoryRowDelegate {
                                width:
                                    historyListView.width
                            }
                        }

                        // ========================================
                        // Empty State
                        // ========================================

                        ColumnLayout {
                            anchors.centerIn: parent

                            visible:
                                root.historyViewModel.count === 0

                            spacing: 6

                            Label {
                                Layout.alignment:
                                    Qt.AlignHCenter

                                text:
                                    root.historyViewModel.totalCount === 0
                                    ? "변경 이력이 없습니다."
                                    : "조건에 맞는 이력이 없습니다."

                                color:
                                    theme.textSecondary

                                font.pixelSize: 13
                            }

                            Label {
                                Layout.alignment:
                                    Qt.AlignHCenter

                                visible:
                                    root.historyViewModel.totalCount > 0

                                text:
                                    "검색어나 필터 조건을 변경해보세요."

                                color:
                                    theme.textMuted

                                font.pixelSize: 11
                            }
                        }
                    }
                }
            }
        }
    }
}