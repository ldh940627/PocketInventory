import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "components"

ApplicationWindow {
    width: 500
    height: 850
    visible: true
    title: qsTr("내 손안의 재고")

    property int normalStockCount : 0
    property int lowStockCount : 0
    property int searchResultCount: 0


    ListModel{
        id: productModel
    }

    function updateStockSummary(){
        let lowCount = 0

        for(let i = 0; i < productModel.count; i++)
        {
            const product = productModel.get(i)
            if(product.productQuantity <= product.minimumQuantity){
                lowCount++
            }
        }
        lowStockCount = lowCount
        normalStockCount = productModel.count - lowCount
    }

    function matchesSearch(productName){
        const keyword = String(searchBar.searchText ?? "")
        .trim().toLowerCase()
        const name = productName.toLowerCase()

        if(keyword === ""){
            return true
        }

        return name.includes(keyword)
    }

    function matchesStockFilter(productQuantity, minimumQuantity)
    {
        const quantity = Number(productQuantity ?? 0)
        const minimum = Number(minimumQuantity ?? 0)

        switch(filterBar.selectedFilter){
        case "normal":
            return quantity > minimum
        case "low":
            return quantity <= minimum
        default:
            return true
        }
    }

    function matchesProduct(productName, productQuantity, minimumQuantity){
        return matchesSearch(productName) && matchesStockFilter(productQuantity, minimumQuantity)
    }

    function updateSearchResultCount(){
        let resultCount = 0

        for(let i = 0; i < productModel.count; i++ ){
            const product = productModel.get(i)
            if(matchesProduct(product.productName, product.productQuantity, product.minimumQuantity)){
                resultCount++
            }
        }

        searchResultCount = resultCount
    }

    function decreaseProductQuantity(productIndex){
        const product = productModel.get(productIndex)

        if(product.productQuantity <= 0){
            messageLabel.text = "재고는 0개보다 작을 수 없습니다."
            messageLabel.color = "red"
            return
        }

        const newQuantity = product.productQuantity - 1

        productModel.setProperty(productIndex, "productQuantity", newQuantity)

        updateStockSummary()
        updateSearchResultCount()

        messageLabel.text = product.productName + " 수량을 " + newQuantity + "개로 변경했습니다."
        messageLabel.color = "green"
    }

    function increaseProductQuantity(productIndex){
        const product = productModel.get(productIndex)
        const newQuantity = product.productQuantity + 1

        productModel.setProperty(productIndex, "productQuantity", newQuantity)

        updateStockSummary()
        updateSearchResultCount()

        messageLabel.text = product.productName + "수량을" + newQuantity + "개로 변경했습니다."
        messageLabel.color = "green"
    }

    function deleteProduct(productIndex){
        const product = productModel.get(productIndex)
        const deletedName = product.productName

        productModel.remove(productIndex)

        updateStockSummary()
        updateSearchResultCount()

        messageLabel.text = deletedName + " 상품을 삭제했습니다."
        messageLabel.color = "darkorange"
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
                       value: normalStockCount + "개"
                       cardColor: "#e5f6ea"
                       valueColor: "green"
                   }

                   SummaryCard{
                       title: "부족 재고"
                       value: lowStockCount + "개"
                       cardColor: "#ffe5e5"
                       valueColor: "red"

                   }
                }

                Label{
                    text: "상품 등록"
                    font.pixelSize: 26
                    font.bold: true
                }

                Label{
                    id: messageLabel

                    text:""
                    visible: text !== ""

                    Layout.fillWidth: true

                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WordWrap

                    color: "green"
                    font.pixelSize: 15
                }

                Label{
                    text: "상품명"
                }

                TextField{
                    id: nameField

                    Layout.fillWidth: true
                    placeholderText: "상품명을 입력하세요"
                }

                Label{
                    text: "현재 수량"
                }

                TextField{
                    id: quantityField

                    Layout.fillWidth: true
                    placeholderText: "수량을 입력하세요"

                    inputMethodHints: Qt.ImhDigitsOnly

                    validator: IntValidator{
                        bottom: 0
                    }
                }

                Label{
                    text: "최소 재고"
                }

                TextField{
                    id: minimumQuantityField

                    Layout.fillWidth: true
                    placeholderText: "최소 재고 수량을 입력하세요"

                    inputMethodHints: Qt.ImhDigitsOnly

                    validator: IntValidator{
                        bottom: 0
                    }
                }


                Button{
                    text: "상품등록"

                    Layout.fillWidth: true

                    onClicked:{
                       const newProductName = nameField.text.trim()

                       if(newProductName === ""){
                           messageLabel.text = "상품명을 입력하세요."
                           messageLabel.color = "red"
                           return
                       }

                       if(quantityField.text === "")
                       {
                           messageLabel.text = "수량을 입력하세요."
                           messageLabel.color = "red"
                           return
                       }

                       if(minimumQuantityField.text === ""){
                           messageLabel.text = "최소 재고를 입력하세요."
                           messageLabel.color = "red"
                           return
                       }

                       for(let i = 0; i < productModel.count; i++){
                           const product = productModel.get(i)
                           if(product.productName.toLowerCase() === newProductName.toLowerCase()){
                               messageLabel.text =
                                       newProductName + "상품은 이미 등록되어 있습니다."
                               messageLabel.color = "red"
                               return
                           }
                       }

                       productModel.append({
                            productName:newProductName,
                            productQuantity:Number(quantityField.text),
                            minimumQuantity:Number(minimumQuantityField.text)
                        })

                       updateStockSummary()
                       updateSearchResultCount()

                       messageLabel.text = newProductName + "상품이 등록되었습니다."
                       messageLabel.color = "green"

                       nameField.text = ""
                       quantityField.text = ""
                       minimumQuantityField.text = ""
                       nameField.forceActiveFocus()
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
                        updateSearchResultCount()
                    }

                    onClearRequested: {
                        filterBar.resetFilter()
                        updateSearchResultCount()
                        messageLabel.text = "검색 조건을 초기화했습니다."
                        messageLabel.color = "gray"
                    }
                }

                Label {
                    text: "검색 결과: " + searchResultCount + "개"
                    color: "gray"
                }

                FilterBar{
                    id: filterBar

                    Layout.fillWidth: true

                    onFilterChanged: function(filter){
                        updateSearchResultCount()

                        switch(filter){
                        case "normal":
                            messageLabel.text = "정상 재고 상품만 표시합니다."
                            break
                        case "low":
                            messageLabel.text = "재고 부족 상품만 표시합니다."
                            break
                        default:
                            messageLabel.text = "전체 상품을 표시합니다."
                            break
                        }

                        messageLabel.color = "gray"
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

                    visible: productModel.count > 0 && searchResultCount === 0
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

                    model: productModel
                    spacing: 0
                    interactive: false

                    delegate: ProductDelegate{

                        width: productListView.width

                        filterMatched: matchesProduct(productName, productQuantity, minimumQuantity)

                        onDecreaseRequested: function(productIndex){
                            decreaseProductQuantity(productIndex)
                        }

                        onIncreaseRequested: function(productIndex){
                            increaseProductQuantity(productIndex)
                        }

                        onDeleteRequested: function(productIndex){
                            deleteProduct(productIndex)
                        }
                    }
                }

            }
        }
    }

}
