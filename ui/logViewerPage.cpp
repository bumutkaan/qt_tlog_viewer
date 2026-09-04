

#include "ui/ui_logViewerWidget.h"
#include "logViewerPage.hpp"

logViewerPage::logViewerPage(QWidget * parent) :
    ui(new Ui::logViewerWidget)
{

}
logViewerPage::~logViewerPage(){
    delete ui;
}
void logViewerPage::setup_ui(){
    ui->setupUi(this);

    connect(ui->tableWidget,&QTableWidget::itemSelectionChanged,[this](){
        int row = ui->tableWidget->currentRow();
        emit rowClicked(row);
    });

    resize_table_columns();

}

void logViewerPage::append_log_data()
{
    if(tlogParser::m_data.size() > 0)
    {
    TelemetryData data = tlogParser::m_data[tlogParser::m_data.size()-1];

    QString time = QString::fromStdString( std::to_string(data.second) + ":" + std::to_string(data.m_second).substr(0,2) );

    std::string data_str = "";
    data_str+="latitude:"+std::to_string(data.latitude)+"; ";
    data_str+="longitude:"+std::to_string(data.longitude)+"; ";
    data_str+="altitude:"+std::to_string(data.altitude)+"; ";
    data_str+="relative_alt:"+std::to_string(data.relative_alt)+"; ";
    data_str+="heading:"+std::to_string(data.heading)+"; ";
    data_str+="vx:"+std::to_string(data.vx)+"; ";
    data_str+="vy:"+std::to_string(data.vy)+"; ";
    data_str+="vz:"+std::to_string(data.vz)+"; ";

    append_data_to_table(time,"GLOBAL_POSITION_INT", QString::fromStdString(data_str));
    }
}

void logViewerPage::append_data_to_table(QString s1,QString s2,QString s3)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    ui->tableWidget->setItem(row, 0,
                             new QTableWidgetItem(s1));

    ui->tableWidget->setItem(row, 1,
                             new QTableWidgetItem(s2));

    ui->tableWidget->setItem(row, 2,
                             new QTableWidgetItem(s3));
}

void logViewerPage::resize_table_columns()
{
    int width = ui->tableWidget->viewport()->width();

    ui->tableWidget->setColumnWidth(0, width * 10 / 100);
    ui->tableWidget->setColumnWidth(1, width * 20 / 100);
    ui->tableWidget->setColumnWidth(2, width * 70 / 100);
}

void logViewerPage::set_index(int index)
{
    ui->tableWidget->selectRow(index);
}