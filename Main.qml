import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "components"

ApplicationWindow {

    required property var productModel
    required property var productFilterModel

    width: 500
    height: 850
    visible: true
    title: qsTr("내 손안의 재고")


    function showMessage(message, colorName = "gray"){
        messageLabel.text = message
        messageLabel.color = colorName
    }

    function decreaseProductQuantity(productIndex) {
        const product = productModel.get(productIndex)

        if(!productModel.decreaseQuantity(productIndex)){
            showMessage("재고는 0개보다 작을 수 없습니다.", "red")
            return
        }

        const updateProduct = productModel.get(productIndex)

        showMessage(
            updateProduct.productName
            + " 수량을 "
            + updateProduct.productQuantity
            + "개로 변경했습니다.",
            "green"
        )
    }

    function increaseProductQuantity(productIndex) {
        if(!productModel.increaseQuantity(productIndex)){
            showMessage("수량 변경에 실패했습니다.", "red")
            return
        }

        const updatedProduct = productModel.get(productIndex)

        showMessage(
            updatedProduct.productName
            + " 수량을 "
            + updatedProduct.productQuantity
            + "개로 변경했습니다.",
            "green"
        )
    }

    function deleteProduct(productIndex) {
        const product = productModel.get(productIndex)
        if(!product.productName){
            showMessage("삭제할 상품을 찾을 수 없습니다.", "red")
            return
        }

        const deletedName = product.productName

        if(!productModel.removeProduct(productIndex)){
            showMessage("상품 삭제에 실패했습니다.", "red")
            return
        }

        showMessage(
            deletedName + " 상품을 삭제했습니다.",
            "darkorange"
        )
    }

    function addProduct(
        productNameText,
        productQuantityText,
        minimumQuantityText
    ) {
        const productName =
                String(productNameText ?? "").trim()

        const quantityText =
                String(productQuantityText ?? "").trim()

        const minimumText =
                String(minimumQuantityText ?? "").trim()

        if (productName === "") {
            showMessage(
                "상품명을 입력해주세요.",
                "red"
            )

            productForm.focusNameField()
            return
        }

        if (quantityText === "") {
            showMessage(
                "현재 수량을 입력해주세요.",
                "red"
            )
            return
        }

        if (minimumText === "") {
            showMessage(
                "최소 수량을 입력해주세요.",
                "red"
            )
            return
        }

        const productQuantity = Number(quantityText)
        const minimumQuantity = Number(minimumText)

        if (!Number.isInteger(productQuantity)
                || productQuantity < 0) {
            showMessage(
                "현재 수량은 0 이상의 정수여야 합니다.",
                "red"
            )
            return
        }

        if (!Number.isInteger(minimumQuantity)
                || minimumQuantity < 0) {
            showMessage(
                "최소 수량은 0 이상의 정수여야 합니다.",
                "red"
            )
            return
        }

        if (productModel.containsProduct(productName)) {
            showMessage(
                productName
                + " 상품은 이미 등록되어 있습니다.",
                "red"
            )

            productForm.focusNameField()
            return
        }

        const added = productModel.addProduct(productName, productQuantity, minimumQuantity)

        if(!added){
            showMessage("상품 등록에 실패했습니다.", "red")
            return
        }

        showMessage(
            productName + " 상품이 등록되었습니다.",
            "green"
        )

        productForm.resetForm()
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
                       value: productModel.count + "개"
                       cardColor: "#e8f0fe"
                       valueColor: "black"
                   }

                   SummaryCard{
                       title: "정상 재고"
                       value: productModel.normalStockCount + "개"
                       cardColor: "#e5f6ea"
                       valueColor: "green"
                   }

                   SummaryCard{
                       title: "부족 재고"
                       value: productModel.lowStockCount + "개"
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
                        addProduct(productName,productQuantity,minimumQuantity)
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
                        productFilterModel.searchText = searchText
                    }

                    onClearRequested: {
                        filterBar.resetFilter()

                        productFilterModel.searchText = ""
                        productFilterModel.stockFilter = "all"

                        showMessage(
                               "검색 조건을 초기화했습니다.",
                               "gray"
                           )
                    }
                }

                Label {
                    text: "검색 결과: " + productFilterModel.count + "개"
                    color: "gray"
                }

                FilterBar{
                    id: filterBar

                    Layout.fillWidth: true

                    onFilterChanged: function(filter) {
                        productFilterModel.stockFilter = filter

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

                    visible: productModel.count > 0 && productFilterModel.count === 0
                }

                Label{
                    Layout.fillWidth: true
                    text: "등록된 상품이 없습니다."
                    horizontalAlignment: Text.AlignHCenter
                    color: "gray"
                    visible: productModel.count === 0
                }

                ListView {
                    id: productListView

                    Layout.fillWidth: true
                    Layout.preferredHeight: Math.max(contentHeight, 200)

                    model: productFilterModel
                    spacing: 0
                    interactive: false

                    delegate: ProductDelegate{

                       width: productListView.width


                       onDecreaseRequested: function(proxyIndex){
                           const originalIndex = productFilterModel.sourceIndex(proxyIndex)
                           decreaseProductQuantity(originalIndex)
                       }

                       onIncreaseRequested: function(proxyIndex){
                           const originalIndex = productFilterModel.sourceIndex(proxyIndex)
                           increaseProductQuantity(originalIndex)
                       }

                       onDeleteRequested: function(proxyIndex){
                           const originalIndex = productFilterModel.sourceIndex(proxyIndex)
                           deleteProduct(originalIndex)
                       }
                    }
                }

            }
        }
    }

}
