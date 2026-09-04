add_library(uiWindow STATIC 
window.cpp
fileSelectPage.cpp
mapPage.cpp
logViewerPage.cpp
mainPage.cpp
)

find_package(Qt5 COMPONENTS Widgets Quick
    Qml
    QuickWidgets
    Location
    Positioning)
find_package(Qt5Widgets)
find_package(Qt5 REQUIRED COMPONENTS Core)

target_link_libraries(uiWindow Qt5::Widgets Qt5::Core Qt5::Quick
    Qt5::Qml
    Qt5::QuickWidgets
    Qt5::Location
    Qt5::Positioning Qt5::Network tlogParser)


target_include_directories(uiWindow PUBLIC "./")