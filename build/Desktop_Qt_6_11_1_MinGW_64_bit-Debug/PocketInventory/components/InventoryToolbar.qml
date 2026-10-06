import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    required property var inventoryViewModel

    signal addProductRequested()
    signal exportCsvRequested()
    signal importCsvRequested()

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

        ComboBox {
            id: categoryComboBox

            Layout.preferredWidth: 150
            Layout.preferredHeight: 36

            model: ["전체 카테고리", "미분류"].concat(root.inventoryViewModel.categories)

            onActivated: {
                if(currentIndex === 0){
                    root.inventoryViewModel.categoryFilter = "all"
                }
                else if(currentIndex === 1){
                    root.inventoryViewModel.categoryFilter = "uncategorized"
                }
                else{
                    root.inventoryViewModel.categoryFilter = currentText
                }
            }

            contentItem: Text {
                leftPadding: 12
                rightPadding: 30

                text: categoryComboBox.displayText
                color: theme.textPrimary

                font.pixelSize: 12

                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            indicator: Text {
                x: categoryComboBox.width - width - 12
                y: (categoryComboBox.height - height) / 2

                text: "▼"
                color: theme.textSecondary
                font.pixelSize: 9
            }

            background: Rectangle {
                radius: theme.radiusMedium
                color: categoryComboBox.hovered ? theme.surfaceHover : theme.surface

                border.width: 1
                border.color: categoryComboBox.activeFocus ? theme.primary : theme.border
            }

            popup: Popup {
                y: categoryComboBox.height + 4
                width: categoryComboBox.width

                padding: 4

                contentItem: ListView {
                    implicitHeight: Math.min(contentHeight, 220)
                    clip: true

                    model: categoryComboBox.popup.visible ? categoryComboBox.delegateModel : null
                    currentIndex: categoryComboBox.highlightedIndex

                    ScrollIndicator.vertical: ScrollIndicator {}
                }

                background: Rectangle {
                    radius: theme.radiusMedium
                    color: theme.surface
                    border.width: 1
                    border.color: theme.border
                }
            }

            delegate: ItemDelegate {
                width: categoryComboBox.width - 8
                height: 34

                highlighted: categoryComboBox.highlightedIndex === index

                contentItem: Text {
                    text: modelData
                    color: theme.textPrimary
                    font.pixelSize: 12

                    verticalAlignment: Text.AlignVCenter
                    leftPadding: 8
                }

                background: Rectangle {
                    radius: 6
                    color: highlighted ? theme.primarySoft : "transparent"
                }
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

        Button {
            text: "CSV 가져오기"

            onClicked: root.importCsvRequested()
        }

        Button {
            text: "CSV 내보내기"
            enabled: root.inventoryViewModel.totalCount > 0

            onClicked: root.exportCsvRequested()
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

        // =========================
        // Category Connections
        // =========================

        Connections {
            target: root.inventoryViewModel

            function onCategoriesChanged(){
                categoryComboBox.currentIndex = 0
                root.inventoryViewModel.categoryFilter = "all"
            }
        }
    }
}