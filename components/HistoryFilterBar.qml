import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    required property var historyViewModel

    AppTheme {
        id: theme
    }

    implicitHeight: customDateRow.visible ? 100 : 58

    radius: theme.radiusMedium

    color: theme.surface

    border.width: 1
    border.color: theme.border

    ColumnLayout {
        id: mainLayout

        anchors.fill: parent
        anchors.margins: 10

        spacing: 10

        // ====================================================
        // Main toolbar
        // ====================================================

        RowLayout {
            Layout.fillWidth: true

            spacing: 8

            // -------------------------
            // Search
            // -------------------------

            TextField {
                id: searchField

                Layout.fillWidth: true
                Layout.maximumWidth: 420
                Layout.preferredHeight: 38

                placeholderText: "상품명 검색"

                leftPadding: 14
                rightPadding: 14

                onTextChanged: {
                    root.historyViewModel.searchText = text
                }

                background: Rectangle {
                    radius: 7

                    color: theme.surfaceSoft

                    border.width: 1

                    border.color:
                        searchField.activeFocus
                        ? theme.primary
                        : theme.border
                }
            }

            Item {
                Layout.fillWidth: true
            }

            // -------------------------
            // Action
            // -------------------------

            ComboBox {
                id: actionCombo

                Layout.preferredWidth: 110
                Layout.preferredHeight: 38

                model: [
                    "전체 유형",
                    "등록",
                    "입고",
                    "출고",
                    "증가",
                    "감소",
                    "삭제"
                ]

                onActivated: {
                    switch (currentIndex) {
                    case 1:
                        root.historyViewModel.actionFilter = "create"
                        break

                    case 2:
                        root.historyViewModel.actionFilter = "purchase"
                        break

                    case 3:
                        root.historyViewModel.actionFilter = "sale"
                        break

                    case 4:
                        root.historyViewModel.actionFilter = "increase"
                        break

                    case 5:
                        root.historyViewModel.actionFilter = "decrease"
                        break

                    case 6:
                        root.historyViewModel.actionFilter = "delete"
                        break

                    default:
                        root.historyViewModel.actionFilter = "all"
                        break
                    }
                }
            }

            // -------------------------
            // Date
            // -------------------------

            ComboBox {
                id: dateCombo

                Layout.preferredWidth: 110
                Layout.preferredHeight: 38

                model: [
                    "전체 기간",
                    "오늘",
                    "최근 7일",
                    "최근 30일",
                    "직접 지정"
                ]

                onActivated: {
                    switch (currentIndex) {
                    case 1:
                        root.historyViewModel.showToday()
                        break

                    case 2:
                        root.historyViewModel.showLast7Days()
                        break

                    case 3:
                        root.historyViewModel.showLast30Days()
                        break

                    case 4:
                        break

                    default:
                        root.historyViewModel.showAllDates()
                        break
                    }
                }
            }

            // -------------------------
            // Sort
            // -------------------------

            ComboBox {
                id: sortCombo

                Layout.preferredWidth: 105
                Layout.preferredHeight: 38

                model: [
                    "최신순",
                    "오래된순"
                ]

                onActivated: {
                    if (currentIndex === 0)
                        root.historyViewModel.sortNewestFirst()
                    else
                        root.historyViewModel.sortOldestFirst()
                }
            }
        }

        // ====================================================
        // Custom date
        // 직접 지정 선택 시에만 나타남
        // ====================================================

        RowLayout {

            id: customDateRow

            Layout.fillWidth: true

            spacing: 8

            visible:
                dateCombo.currentIndex === 4

            TextField {
                id: fromDateField

                Layout.preferredWidth: 150
                Layout.preferredHeight: 36

                placeholderText: "2026-08-01"
            }

            Label {
                text: "–"

                color: theme.textMuted
            }

            TextField {
                id: toDateField

                Layout.preferredWidth: 150
                Layout.preferredHeight: 36

                placeholderText: "2026-08-12"
            }

            Button {
                text: "적용"

                implicitHeight: 36

                onClicked: {
                    root.historyViewModel.setDateRange(
                        fromDateField.text,
                        toDateField.text
                    )
                }
            }

            Item {
                Layout.fillWidth: true
            }
        }
    }
}