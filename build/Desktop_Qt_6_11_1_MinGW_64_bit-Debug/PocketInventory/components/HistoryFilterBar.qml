import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    required property var historyViewModel

    implicitHeight: contentLayout.implicitHeight + 24

    radius: 8
    color: "#f5f5f5"

    ColumnLayout {
        id: contentLayout

        anchors.fill: parent
        anchors.margins: 12
        spacing: 12

        // =========================
        // 상품명 검색
        // =========================

        SearchBar {
            id: historySearchBar

            Layout.fillWidth: true

            placeholderText:
                "이력 상품명을 검색하세요"

            onSearchRequested: function(searchText) {
                root.historyViewModel.searchText =
                        searchText
            }

            onClearRequested: {
                root.historyViewModel.resetFilters()

                fromDateField.clear()
                toDateField.clear()
            }
        }

        // =========================
        // 액션 필터
        // =========================

        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            Label {
                text: "이력 필터"
                font.bold: true
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                text: "전체"
                checkable: true

                checked:
                    root.historyViewModel.actionFilter
                    === "all"

                onClicked: {
                    root.historyViewModel.actionFilter =
                            "all"
                }
            }

            Button {
                text: "입고"
                checkable: true

                checked:
                    root.historyViewModel.actionFilter
                    === "purchase"

                onClicked: {
                    root.historyViewModel.actionFilter =
                            "purchase"
                }
            }

            Button {
                text: "출고"
                checkable: true

                checked:
                    root.historyViewModel.actionFilter
                    === "sale"

                onClicked: {
                    root.historyViewModel.actionFilter =
                            "sale"
                }
            }

            Button {
                text: "등록"
                checkable: true

                checked:
                    root.historyViewModel.actionFilter
                    === "create"

                onClicked: {
                    root.historyViewModel.actionFilter =
                            "create"
                }
            }

            Button {
                text: "증가"
                checkable: true

                checked:
                    root.historyViewModel.actionFilter
                    === "increase"

                onClicked: {
                    root.historyViewModel.actionFilter =
                            "increase"
                }
            }

            Button {
                text: "감소"
                checkable: true

                checked:
                    root.historyViewModel.actionFilter
                    === "decrease"

                onClicked: {
                    root.historyViewModel.actionFilter =
                            "decrease"
                }
            }

            Button {
                text: "삭제"
                checkable: true

                checked:
                    root.historyViewModel.actionFilter
                    === "delete"

                onClicked: {
                    root.historyViewModel.actionFilter =
                            "delete"
                }
            }
        }

        // =========================
        // 기간 프리셋
        // =========================

        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            Label {
                text: "기간"
                font.bold: true
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                text: "전체"
                checkable: true

                checked:
                    root.historyViewModel.datePreset
                    === "all"

                onClicked: {
                    root.historyViewModel.showAllDates()
                }
            }

            Button {
                text: "오늘"
                checkable: true

                checked:
                    root.historyViewModel.datePreset
                    === "today"

                onClicked: {
                    root.historyViewModel.showToday()
                }
            }

            Button {
                text: "7일"
                checkable: true

                checked:
                    root.historyViewModel.datePreset
                    === "7days"

                onClicked: {
                    root.historyViewModel.showLast7Days()
                }
            }

            Button {
                text: "30일"
                checkable: true

                checked:
                    root.historyViewModel.datePreset
                    === "30days"

                onClicked: {
                    root.historyViewModel.showLast30Days()
                }
            }
        }

        // =========================
        // 직접 날짜 지정
        // =========================

        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            TextField {
                id: fromDateField

                Layout.fillWidth: true

                placeholderText:
                    "시작일 yyyy-MM-dd"
            }

            Label {
                text: "~"
            }

            TextField {
                id: toDateField

                Layout.fillWidth: true

                placeholderText:
                    "종료일 yyyy-MM-dd"
            }

            Button {
                text: "적용"

                onClicked: {
                    root.historyViewModel.setDateRange(
                        fromDateField.text,
                        toDateField.text
                    )
                }
            }
        }

        Label {
            visible:
                root.historyViewModel.datePreset
                === "custom"

            text: "직접 지정 기간 적용 중"

            color: "gray"
            font.pixelSize: 12
        }

        // =========================
        // 정렬
        // =========================

        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            Label {
                text: "정렬"
                font.bold: true
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                text: "최신순"
                checkable: true

                checked:
                    root.historyViewModel.sortOrder
                    === "newest"

                onClicked: {
                    root.historyViewModel
                        .sortNewestFirst()
                }
            }

            Button {
                text: "오래된순"
                checkable: true

                checked:
                    root.historyViewModel.sortOrder
                    === "oldest"

                onClicked: {
                    root.historyViewModel
                        .sortOldestFirst()
                }
            }
        }

        // =========================
        // 결과
        // =========================

        Label {
            text:
                "검색 결과: "
                + root.historyViewModel.count
                + "건"

            color: "gray"
        }
    }
}