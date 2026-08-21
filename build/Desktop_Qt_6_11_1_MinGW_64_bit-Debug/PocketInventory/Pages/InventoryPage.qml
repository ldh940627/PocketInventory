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

    // ============================================================
    // Content Container
    // ============================================================

    Item {
        id: contentContainer

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        width: Math.min(
            parent.width - 56,
            theme.pageMaxWidth
        )

        ColumnLayout {
            anchors.fill: parent

            anchors.topMargin: theme.pageMargin
            anchors.bottomMargin: theme.pageMargin

            spacing: theme.sectionSpacing

            // ====================================================
            // Header
            // ====================================================

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
                    text: "상품과 현재 재고 상태를 관리합니다."

                    font.pixelSize: 13

                    color: theme.textSecondary
                }
            }

            // ====================================================
            // Toolbar
            // ====================================================

            InventoryToolbar {
                Layout.fillWidth: true

                inventoryViewModel:
                    root.inventoryViewModel

                onAddProductRequested: {
                    productDialog.open()
                }
            }

            // ====================================================
            // Count
            // ====================================================

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

            // ====================================================
            // Product Table
            // ====================================================

            InventoryTable {
                Layout.fillWidth: true
                Layout.fillHeight: true

                inventoryViewModel:
                    root.inventoryViewModel

                // ------------------------------------------------
                // 입고
                // ------------------------------------------------

                onReceiveRequested:
                    function(
                        proxyIndex,
                        productName,
                        currentQuantity
                    ) {
                        stockAdjustDialog.openReceive(
                            proxyIndex,
                            productName,
                            currentQuantity
                        )
                    }

                // ------------------------------------------------
                // 출고
                // ------------------------------------------------

                onReleaseRequested:
                    function(
                        proxyIndex,
                        productName,
                        currentQuantity
                    ) {
                        stockAdjustDialog.openRelease(
                            proxyIndex,
                            productName,
                            currentQuantity
                        )
                    }

                // ------------------------------------------------
                // 수정
                // ------------------------------------------------

                onEditRequested:
                    function(
                        proxyIndex,
                        productName,
                        currentQuantity,
                        minimumQuantity,
                        unitPrice
                    ){
                        editProductDialog.openEdit(
                            proxyIndex,
                            productName,
                            currentQuantity,
                            minimumQuantity,
                            unitPrice
                        )
                    }

                // ------------------------------------------------
                // 삭제
                // ------------------------------------------------

                onDeleteRequested:
                    function(
                        proxyIndex,
                        productName
                    ) {
                        deleteDialog.openDelete(
                            proxyIndex,
                            productName
                        )
                    }
            }
        }
    }

    // ============================================================
    // Product Add Dialog
    // ============================================================

    ProductDialog {
        id: productDialog

        inventoryViewModel: root.inventoryViewModel
    }

    // ============================================================
    // Stock Adjust Dialog
    // 입고 / 출고 공용
    // ============================================================

    StockAdjustDialog {
        id: stockAdjustDialog

        inventoryViewModel: root.inventoryViewModel
    }

    // ============================================================
    // Edit Product Dialog
    // ============================================================

    EditProductDialog{
        id: editProductDialog

        inventoryViewModel: root.inventoryViewModel
    }

    // ============================================================
    // Delete Product Dialog
    // ============================================================

    DeleteProductDialog {
        id: deleteDialog

        inventoryViewModel: root.inventoryViewModel
    }
}