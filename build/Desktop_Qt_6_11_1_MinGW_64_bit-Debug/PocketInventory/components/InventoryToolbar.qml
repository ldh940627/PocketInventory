import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    required property var inventoryViewModel

    signal addProductRequested()

    AppTheme {
        id: theme
    }

    implicitHeight: 42

    RowLayout {
        anchors.fill: parent

        spacing: 10

        // =========================
        // Search
        // =========================

        TextField {
            id: searchField

            Layout.preferredWidth: 320
            Layout.fillHeight: true

            placeholderText: "상품 검색"

            leftPadding: 14
            rightPadding: 14

            onTextChanged: {
                root.inventoryViewModel.searchText = text
            }

            background: Rectangle {
                radius: theme.radiusMedium

                color: theme.surface

                border.width: 1

                border.color:
                    searchField.activeFocus
                    ? theme.primary
                    : theme.border
            }
        }

        // =========================
        // Filter
        // =========================

        RowLayout {
            spacing: 2

            Button {
                id: allButton

                text: "전체"

                checkable: true

                checked:
                    root.inventoryViewModel.stockFilter === "all"

                implicitWidth: 62
                implicitHeight: 34

                onClicked: {
                    root.inventoryViewModel.stockFilter = "all"
                }

                contentItem: Text {
                    text: allButton.text

                    color:
                        allButton.checked
                        ? theme.textPrimary
                        : theme.textSecondary

                    font.pixelSize: 12
                    font.bold: allButton.checked

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    radius: 7

                    color:
                        allButton.checked
                        ? theme.primarySoft
                        : allButton.hovered
                            ? theme.surfaceHover
                            : "transparent"
                }
            }

            Button {
                id: normalButton

                text: "정상"

                checkable: true

                checked:
                    root.inventoryViewModel.stockFilter === "normal"

                implicitWidth: 62
                implicitHeight: 34

                onClicked: {
                    root.inventoryViewModel.stockFilter = "normal"
                }

                contentItem: Text {
                    text: normalButton.text

                    color:
                        normalButton.checked
                        ? theme.success
                        : theme.textSecondary

                    font.pixelSize: 12
                    font.bold: normalButton.checked

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    radius: 7

                    color:
                        normalButton.checked
                        ? theme.successSoft
                        : normalButton.hovered
                            ? theme.surfaceHover
                            : "transparent"
                }
            }

            Button {
                id: lowButton

                text: "부족"

                checkable: true

                checked:
                    root.inventoryViewModel.stockFilter === "low"

                implicitWidth: 62
                implicitHeight: 34

                onClicked: {
                    root.inventoryViewModel.stockFilter = "low"
                }

                contentItem: Text {
                    text: lowButton.text

                    color:
                        lowButton.checked
                        ? theme.danger
                        : theme.textSecondary

                    font.pixelSize: 12
                    font.bold: lowButton.checked

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    radius: 7

                    color:
                        lowButton.checked
                        ? theme.dangerSoft
                        : lowButton.hovered
                            ? theme.surfaceHover
                            : "transparent"
                }
            }
        }

        Item {
            Layout.fillWidth: true
        }

        // =========================
        // Add Product
        // =========================

        Button {
            id: addButton

            text: "+ 상품 등록"

            implicitWidth: 104
            implicitHeight: 36

            onClicked: {
                root.addProductRequested()
            }

            contentItem: Text {
                text: addButton.text

                color: "white"

                font.pixelSize: 12
                font.bold: true

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                radius: 7

                color:
                    addButton.hovered
                    ? theme.primaryHover
                    : theme.primary
            }
        }
    }
}