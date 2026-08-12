cmake_minimum_required(VERSION 3.16)

project(PocketInventory VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Sql QuickControls2)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appPocketInventory
    main.cpp
    productmodel.cpp
    productmodel.h
)

qt_add_qml_module(appPocketInventory
    URI PocketInventory
    QML_FILES
        Main.qml
        QML_FILES components/SummaryCard.qml
        QML_FILES components/ProductDelegate.qml
        QML_FILES components/SearchBar.qml
        QML_FILES components/FilterBar.qml
        QML_FILES components/ProductForm.qml
        SOURCES productmodel.h productmodel.cpp
        SOURCES productfilterproxymodel.h productfilterproxymodel.cpp
        SOURCES inventoryviewmodel.h inventoryviewmodel.cpp
        SOURCES DatabaseManager.h DatabaseManager.cpp
        SOURCES productrepository.h productrepository.cpp
        SOURCES HistoryRecord.h
        SOURCES historyrepository.h historyrepository.cpp
        SOURCES inventoryservice.h inventoryservice.cpp
        SOURCES historymodel.h historymodel.cpp
        SOURCES historyviewmodel.h historyviewmodel.cpp
        QML_FILES components/HistoryDelegate.qml
        SOURCES historyfilterproxymodel.h historyfilterproxymodel.cpp
        QML_FILES components/HistoryFilterBar.qml
        QML_FILES components/AppTheme.qml
        QML_FILES components/NavButton.qml
        QML_FILES components/AppSidebar.qml
        QML_FILES components/AppHeader.qml
        QML_FILES components/AppToast.qml
        QML_FILES components/DashboardStatCard.qml
        QML_FILES components/DashboardPanel.qml
        QML_FILES components/LowStockDashboardDelegate.qml
        QML_FILES components/RecentHistoryDelegate.qml
        QML_FILES Pages/DashboardPage.qml
        QML_FILES components/InventoryRowDelegate.qml
        QML_FILES components/ProductDialog.qml
        QML_FILES Pages/InventoryPage.qml
        QML_FILES Pages/HistoryPage.qml
        QML_FILES components/HistoryRowDelegate.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appPocketInventory PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appPocketInventory
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appPocketInventory
    PRIVATE Qt6::Quick Qt6::Sql Qt6::QuickControls2
)

install(TARGETS appPocketInventory
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
