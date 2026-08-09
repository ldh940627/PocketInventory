import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "components"

ApplicationWindow {

    id: rootWindow

    required property var inventoryViewModel
    required property var historyViewModel

    width: 500
    height: 850
    visible: true
    title: qsTr("내 손안의 재고")


    function showMessage(message, colorName = "gray"){
        messageLabel.text = message
        messageLabel.color = colorName
    }

    Connections{
        target: inventoryViewModel

        function onMessageRequested(message, colorName){
            showMessage(message, colorName)
        }
    }

    ScrollView{
        anchors.fill: parent
        clip:true
        contentWidth: availableWidth

        Pane{
            width: parent.width
            padding:30

            ColumnLayout {
                width: parent.width
                spacing: 15
                RowLayout{
                    Layout.fillWidth: true
                    spacing: 10

                   SummaryCard{
                       title: "전체 상품"
                       value: inventoryViewModel.totalCount + "개"
                       cardColor: "#e8f0fe"
                       valueColor: "black"
                   }

                   SummaryCard{
                       title: "정상 재고"
                       value: inventoryViewModel.normalStockCount + "개"
                       cardColor: "#e5f6ea"
                       valueColor: "green"
                   }

                   SummaryCard{
                       title: "부족 재고"
                       value: inventoryViewModel.lowStockCount + "개"
                       cardColor: "#ffe5e5"
                       valueColor: "red"

                   }
                }

                Label {
                    id: messageLabel

                    text: ""
                    visible: text !== ""

                    Layout.fillWidth: true

                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WordWrap

                    color: "green"
                    font.pixelSize: 15
                }

                ProductForm{
                    id: productForm

                    Layout.fillWidth: true

                    onSubmitRequested: function(
                        productName,
                        productQuantity,
                        minimumQuantity)
                    {
                        const succeeded = inventoryViewModel.addProduct(productName, productQuantity, minimumQuantity)

                        if(succeeded)
                            productForm.resetForm()
                    }
                }


                Rectangle{
                    Layout.fillWidth: true
                    height: 1
                    color: "lightgray"
                }

                SearchBar{
                    id: searchBar

                    Layout.fillWidth: true
                    onSearchRequested: function(searchText){
                        inventoryViewModel.searchText = searchText
                    }

                    onClearRequested: {
                        filterBar.resetFilter()
                        inventoryViewModel.resetFilters()
                    }
                }

                Label {
                    text: "검색 결과: " + inventoryViewModel.filteredCount + "개"
                    color: "gray"
                }

                FilterBar{
                    id: filterBar

                    Layout.fillWidth: true

                    onFilterChanged: function(filter) {
                        inventoryViewModel.stockFilter = filter

                        switch (filter) {
                        case "normal":
                            showMessage(
                                "정상 재고 상품만 표시합니다.",
                                "gray"
                            )
                            break

                        case "low":
                            showMessage(
                                "재고 부족 상품만 표시합니다.",
                                "gray"
                            )
                            break

                        default:
                            showMessage(
                                "전체 상품을 표시합니다.",
                                "gray"
                            )
                            break
                        }
                    }
                }



                Label {
                    text: "상품 목록"
                    font.pixelSize: 22
                    font.bold: true
                }

                Label{
                    Layout.fillWidth: true
                    text:"조건에 맞는 상품이 없습니다."
                    horizontalAlignment: Text.AlignHCenter
                    color : "gray"

                    visible: inventoryViewModel.totalCount > 0 && inventoryViewModel.filteredCount === 0
                }

                Label{
                    Layout.fillWidth: true
                    text: "등록된 상품이 없습니다."
                    horizontalAlignment: Text.AlignHCenter
                    color: "gray"
                    visible: inventoryViewModel.totalCount === 0
                }

                ListView {
                    id: productListView

                    Layout.fillWidth: true
                    Layout.preferredHeight: Math.max(contentHeight, 200)

                    model: inventoryViewModel.products
                    spacing: 0
                    interactive: false

                    delegate: ProductDelegate{

                       width: productListView.width


                       onDecreaseRequested: function(proxyIndex){
                           inventoryViewModel.decreaseQuantity(proxyIndex)
                       }

                       onIncreaseRequested: function(proxyIndex){
                           inventoryViewModel.increaseQuantity(proxyIndex)
                       }

                       onDeleteRequested: function(proxyIndex){
                           inventoryViewModel.removeProduct(proxyIndex)
                       }

                       onReceiveRequested: function(proxyIndex, quantityText){
                           const succeeded = inventoryViewModel.receiveStock(proxyIndex, quantityText)
                       }

                       onReleaseRequested: function(proxyIndex, quantityText){
                           inventoryViewModel.releaseStock(proxyIndex, quantityText)
                       }
                    }
                }

                Rectangle{
                    Layout.fillWidth: true
                    height: 1
                    color: "lightgray"
                }

                Label{
                    text: "재고 변경 이력"
                    font.pixelSize: 22
                    font.bold: true
                }

                HistoryFilterBar{
                    Layout.fillWidth: true

                    historyViewModel: rootWindow.historyViewModel
                }

                Label {
                    Layout.fillWidth: true

                    text: "재고 변경 이력이 없습니다."

                    horizontalAlignment:
                        Text.AlignHCenter

                    color: "gray"

                    visible:
                        historyViewModel.count === 0
                }

                ListView {
                    id: historyListView

                    Layout.fillWidth: true

                    Layout.preferredHeight:
                        Math.max(contentHeight, 200)

                    model:
                        historyViewModel.history

                    spacing: 8
                    interactive: false

                    delegate: HistoryDelegate {
                        width: historyListView.width
                    }
                }

            }
        }
    }

}
