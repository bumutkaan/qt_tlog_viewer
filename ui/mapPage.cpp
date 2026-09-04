

#include "ui/ui_mapWidget.h"
#include "mapPage.hpp"

mapPage::mapPage(QWidget * parent) :
    ui(new Ui::mapWidget)
{

}
mapPage::~mapPage(){
    delete ui;
}
void mapPage::setup_ui(){
    ui->setupUi(this);

    ui->quickWidget->setResizeMode(
        QQuickWidget::SizeRootObjectToView
    );


    ui->quickWidget->setSource(
        QUrl("qml/Map.qml")
    );

    /*
    import QtQuick 2.15
    Item {
        id: root
        objectName: "myQmlItem" // Important if you need to find it via findChild()

        function myQmlFunction(message) {
            console.log("QML received:", message)
            return "Success from QML!"
        }
    }
    */


    // --------------
    // QObject *rootObject = ui->quickWidget->rootObject();

    // QVariant returnedValue;
    // QVariant msg = "C++'tan gelen mesaj";

    // // 2. Fonksiyonu tetikleyin
    // bool success = QMetaObject::invokeMethod(
    //     rootObject,
    //     "myQmlFunction", // QML içindeki fonksiyon adı
    //     Q_RETURN_ARG(QVariant, returnedValue),
    //     Q_ARG(QVariant, msg)
    //     );
}

void mapPage::update_map_index(int index)
{

}

void mapPage::append_map_data()
{
    if(tlogParser::m_data.size() > 0)
    {
        TelemetryData data = tlogParser::m_data[tlogParser::m_data.size()-1];

        QObject *rootObject = ui->quickWidget->rootObject();
        if(!rootObject) return;

        // QMetaObject::invokeMethod(
        //     rootObject,
        //     "loggerFunction");

        QMetaObject::invokeMethod(
            rootObject,
            "updateTelemetry",
            Q_ARG(QVariant, data.latitude),
            Q_ARG(QVariant, data.longitude),
            Q_ARG(QVariant, data.heading)
            );
    }
}

void mapPage::set_index(int index)
{
    if(tlogParser::m_data.size() > index)
    {
        TelemetryData data = tlogParser::m_data[index];

        QObject *rootObject = ui->quickWidget->rootObject();
        if(!rootObject) return;

        QMetaObject::invokeMethod(
            rootObject,
            "setIndex",
            Q_ARG(QVariant, data.latitude),
            Q_ARG(QVariant, data.longitude),
            Q_ARG(QVariant, data.heading)
        );
    }
}