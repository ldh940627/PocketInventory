import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "../components"

Item {
    id: root

    required property var inventoryViewModel

    AppTheme {
        id: theme
    }

    Item {
        id: contentContainer

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.horizontalCenter:
            parent.horizontalCenter

        width:
            Math.min(
                parent.width - 56,
                1180
            )

        ColumnLayout {
            anchors.fill: parent

            anchors.topMargin: 28
            anchors.bottomMargin: 28

            spacing: theme.sectionSpacing

            // =========================
            // Header
            // =========================

            RowLayout {
                Layout.fillWidth: true

                ColumnLayout {
                    Layout.fillWidth: true

                    spacing: 3

                    Label {
                        text: "재고 관리"

                        font.pixelSize: 28
                        font.bold: true

                        color: theme.textPrimary
                    }

                    Label {
                        text:
                            "상품의 재고와 입출고를 관리합니다."

                        font.pixelSize: 13

                        color: theme.textSecondary
                    }
                }

                Button {
                    id: addProductButton

                    text: "+ 새 상품"

                    implicitWidth: 110
                    implicitHeight: 38

                    onClicked: {
                        productDialog.open()
                    }

                    contentItem: Text {
                        text: addProductButton.text

                        color: "white"

                        font.pixelSize: 13
                        font.bold: true

                        horizontalAlignment:
                            Text.AlignHCenter

                        verticalAlignment:
                            Text.AlignVCenter
                    }

                    background: Rectangle {
                        radius: 8

                        color:
                            addProductButton.hovered
                            ? theme.primaryHover
                            : theme.primary
                    }
                }
            }

            // =========================
            // Toolbar
            // =========================

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 58

                radius: theme.radiusMedium

                color: theme.surface

                border.width: 1
                border.color: theme.border

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10

                    spacing: 10

                    TextField {
                        id: searchField

                        Layout.preferredWidth: 300
                        Layout.preferredHeight: 38

                        placeholderText: "상품 검색"

                        leftPadding: 14
                        rightPadding: 14

                        onTextChanged: {
                            root.inventoryViewModel.searchText =
                                text
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

                    RowLayout {
                        spacing: 4

                        Button {
                            id: allButton

                            text: "전체"

                            checkable: true

                            checked:
                                root.inventoryViewModel.stockFilter
                                === "all"

                            implicitWidth: 68
                            implicitHeight: 36

                            onClicked: {
                                root.inventoryViewModel.stockFilter =
                                    "all"
                            }

                            contentItem: Text {
                                text: allButton.text

                                color:
                                    allButton.checked
                                    ? theme.primary
                                    : theme.textSecondary

                                font.pixelSize: 12
                                font.bold: allButton.checked

                                horizontalAlignment:
                                    Text.AlignHCenter

                                verticalAlignment:
                                    Text.AlignVCenter
                            }

                            background: Rectangle {
                                radius: 7

                                color:
                                    allButton.checked
                                    ? theme.primarySoft
                                    : allButton.hovered
                                        ? theme.surfaceSoft
                                        : "transparent"

                                border.width:
                                    allButton.checked ? 1 : 0

                                border.color:
                                    theme.primary
                            }
                        }

                        Button {
                            id: normalButton

                            text: "정상"

                            checkable: true

                            checked:
                                root.inventoryViewModel.stockFilter
                                === "normal"

                            implicitWidth: 68
                            implicitHeight: 36

                            onClicked: {
                                root.inventoryViewModel.stockFilter =
                                    "normal"
                            }

                            contentItem: Text {
                                text: normalButton.text

                                color:
                                    normalButton.checked
                                    ? theme.success
                                    : theme.textSecondary

                                font.pixelSize: 12
                                font.bold: normalButton.checked

                                horizontalAlignment:
                                    Text.AlignHCenter

                                verticalAlignment:
                                    Text.AlignVCenter
                            }

                            background: Rectangle {
                                radius: 7

                                color:
                                    normalButton.checked
                                    ? theme.successSoft
                                    : normalButton.hovered
                                        ? theme.surfaceSoft
                                        : "transparent"

                                border.width:
                                    normalButton.checked ? 1 : 0

                                border.color:
                                    theme.success
                            }
                        }

                        Button {
                            id: lowButton

                            text: "부족"

                            checkable: true

                            checked:
                                root.inventoryViewModel.stockFilter
                                === "low"

                            implicitWidth: 68
                            implicitHeight: 36

                            onClicked: {
                                root.inventoryViewModel.stockFilter =
                                    "low"
                            }

                            contentItem: Text {
                                text: lowButton.text

                                color:
                                    lowButton.checked
                                    ? theme.danger
                                    : theme.textSecondary

                                font.pixelSize: 12
                                font.bold: lowButton.checked

                                horizontalAlignment:
                                    Text.AlignHCenter

                                verticalAlignment:
                                    Text.AlignVCenter
                            }

                            background: Rectangle {
                                radius: 7

                                color:
                                    lowButton.checked
                                    ? theme.dangerSoft
                                    : lowButton.hovered
                                        ? theme.surfaceSoft
                                        : "transparent"

                                border.width:
                                    lowButton.checked ? 1 : 0

                                border.color:
                                    theme.danger
                            }
                        }
                    }
                }
            }

            // =========================
            // Count
            // =========================

            RowLayout {
                Layout.fillWidth: true

                Label {
                    text:
                        "상품 "
                        + root.inventoryViewModel.filteredCount
                        + "개"

                    color: theme.textSecondary

                    font.pixelSize: 12
                    font.bold: true
                }

                Item {
                    Layout.fillWidth: true
                }
            }

            // =========================
            // Product Table
            // =========================

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

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 48

                        color: theme.surfaceSoft

                        RowLayout {
                            anchors.fill: parent

                            anchors.leftMargin: 20
                            anchors.rightMargin: 20

                            spacing: 12

                            Label {
                                text: "상품"

                                Layout.fillWidth: true
                                Layout.preferredWidth: 4

                                font.pixelSize: 12
                                font.bold: true

                                color: theme.textSecondary
                            }

                            Label {
                                text: "재고"

                                Layout.preferredWidth: 90

                                font.pixelSize: 12
                                font.bold: true

                                color: theme.textSecondary
                            }

                            Label {
                                text: "최소"

                                Layout.preferredWidth: 90

                                font.pixelSize: 12
                                font.bold: true

                                color: theme.textSecondary
                            }

                            Label {
                                text: "상태"

                                Layout.preferredWidth: 90

                                font.pixelSize: 12
                                font.bold: true

                                color: theme.textSecondary
                            }

                            Item {
                                Layout.preferredWidth: 44
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

                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        ListView {
                            id: productListView

                            anchors.fill: parent

                            clip: true

                            model:
                                root.inventoryViewModel.products

                            delegate:
                                InventoryRowDelegate {

                                    width:
                                        productListView.width

                                    onActionRequested:
                                        function(proxyIndex) {

                                            console.log(
                                                "Action menu:",
                                                proxyIndex
                                            )

                                            // 다음 단계:
                                            // Action Menu 연결
                                        }
                                }
                        }

                        Label {
                            anchors.centerIn: parent

                            visible:
                                root.inventoryViewModel.filteredCount
                                === 0

                            text:
                                root.inventoryViewModel.totalCount
                                === 0
                                ? "등록된 상품이 없습니다."
                                : "조건에 맞는 상품이 없습니다."

                            color:
                                theme.textSecondary

                            font.pixelSize: 13
                        }
                    }
                }
            }
        }
    }

    ProductDialog {
        id: productDialog

        inventoryViewModel:
            root.inventoryViewModel
    }
}