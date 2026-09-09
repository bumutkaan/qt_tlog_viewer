

#include "ui/ui_mainWidget.h"
#include "mainPage.hpp"

mainPage::mainPage(QWidget * parent) :
    ui(new Ui::mainWidget),
    live_playback_timer(new QTimer(this))
{
    live_playback_timer->setInterval(PLAYBACK_TIMEOUT_MS);
}
mainPage::~mainPage(){
    delete ui;
}
void mainPage::setup_ui(){
    ui->setupUi(this);

    log_viewer_page_ptr = new logViewerPage(this);
    log_viewer_page_ptr->set_tlog_parser(tlog_parser_ptr);
    log_viewer_page_ptr->setup_ui();
    ui->stackedWidget->addWidget(log_viewer_page_ptr);

    map_page_ptr = new mapPage(this);
    map_page_ptr->set_tlog_parser(tlog_parser_ptr);
    map_page_ptr->setup_ui();
    ui->stackedWidget->addWidget(map_page_ptr);

    setup_signal_slots();

    ui->stackedWidget->setCurrentWidget(map_page_ptr);
}

void mainPage::setup_signal_slots()
{
    connect(live_playback_timer,&QTimer::timeout,this,&mainPage::live_playback_func);
    connect(ui->open_map_button,&QPushButton::clicked,this,&mainPage::load_map_page);
    connect(ui->open_data_button,&QPushButton::clicked,this,&mainPage::load_data_view_page);
    connect(ui->horizontalSlider,&QSlider::valueChanged,this,&mainPage::slider_position_changed);
    connect(ui->start_stop_button,&QPushButton::clicked,this,&mainPage::start_livepaylack);
    connect(log_viewer_page_ptr,&logViewerPage::rowClicked,this,&mainPage::set_index);
}

void mainPage::set_tlog_parser(tlogParser * ptr)
{
    tlog_parser_ptr = ptr;
}

void mainPage::load_map_page()
{
    ui->open_map_button->setStyleSheet("QPushButton\n{\npadding:10px;\nborder:1px solid rgb(225,225,225);\nborder-radius:5px;\nbackground-color:rgb(225,225,225);\ncolor:black;\n}\nQPushButton::hover\n{\npadding:10px;\nborder:1px solid rgb(100,100,100);\nborder-radius:10px;\nbackground-color:rgb(50,50,50);\ncolor:white;\n}");
    ui->open_data_button->setStyleSheet("QPushButton\n{\npadding:10px;\nborder:1px solid rgb(150,150,150);\nborder-radius:5px;\nbackground-color:rgb(100,100,100);\ncolor:white;\n}\nQPushButton::hover\n{\npadding:10px;\nborder:1px solid rgb(100,100,100);\nborder-radius:10px;\nbackground-color:rgb(50,50,50);\ncolor:white;\n}");
    ui->stackedWidget->setCurrentWidget(map_page_ptr);
}

void mainPage::load_data_view_page()
{
    ui->open_data_button->setStyleSheet("QPushButton\n{\npadding:10px;\nborder:1px solid rgb(225,225,225);\nborder-radius:5px;\nbackground-color:rgb(225,225,225);\ncolor:black;\n}\nQPushButton::hover\n{\npadding:10px;\nborder:1px solid rgb(100,100,100);\nborder-radius:10px;\nbackground-color:rgb(50,50,50);\ncolor:white;\n}");
    ui->open_map_button->setStyleSheet("QPushButton\n{\npadding:10px;\nborder:1px solid rgb(150,150,150);\nborder-radius:5px;\nbackground-color:rgb(100,100,100);\ncolor:white;\n}\nQPushButton::hover\n{\npadding:10px;\nborder:1px solid rgb(100,100,100);\nborder-radius:10px;\nbackground-color:rgb(50,50,50);\ncolor:white;\n}");
    ui->stackedWidget->setCurrentWidget(log_viewer_page_ptr);
    log_viewer_page_ptr->resize_table_columns();
}

void mainPage::set_slider_max_data(int data_size)
{
    if(tlogParser::m_data.size() > 0)
    {
        TelemetryData data = tlogParser::m_data[tlogParser::m_data.size() - 1];
        ui->horizontalSlider->setMaximum(data_size);
        unsigned short munite = data.second /60;
        unsigned short second = data.second % 60;
        // QString time = QString::fromStdString(std::to_string(hours) ":" + std::to_string(data.second) + ":" + std::to_string(data.m_second).substr(0,2) );
        QString time = QString::number(munite) + QString(":") + QString::number(second) +  QString(":") + QString::number(data.m_second);
        ui->slider_max_data_label->setText(time);
    }

}

void mainPage::set_index(int index)
{
    ui->horizontalSlider->setSliderPosition(index);
}

void mainPage::append_data()
{
    map_page_ptr->append_map_data();
    log_viewer_page_ptr->append_log_data();
}

void mainPage::resize_event()
{
    log_viewer_page_ptr->resize_table_columns();
}

void mainPage::slider_position_changed(int value)
{
    if( tlogParser::m_data.size()>value)
    {
        TelemetryData data = tlogParser::m_data[value];
        map_page_ptr->set_index(value);
        log_viewer_page_ptr->set_index(value);
        // QString time = QString::fromStdString( std::to_string(data.second) + ":" + std::to_string(data.m_second).substr(0,2) );

        unsigned short munite = data.second /60;
        unsigned short second = data.second % 60;
        // QString time = QString::fromStdString(std::to_string(hours) ":" + std::to_string(data.second) + ":" + std::to_string(data.m_second).substr(0,2) );
        QString time = QString::number(munite) + QString(":") + QString::number(second) + QString(":") + QString::number(data.m_second);
        ui->slider_data_label->setText(time);
    }

}

void mainPage::live_playback_func()
{
    // t
    // t+1
    // t+ 5
    unsigned int next_index = ui->horizontalSlider->sliderPosition()+1;
    TelemetryData now_data = tlogParser::m_data[ui->horizontalSlider->sliderPosition()];
    if(next_index < tlogParser::m_data.size() )
    {
        TelemetryData next_data = tlogParser::m_data[next_index];

        unsigned int now_second = now_data.second;
        unsigned int now_m_second = now_data.m_second;

        unsigned int next_second = next_data.second;
        unsigned int next_m_second = next_data.m_second;
        int dif_second = static_cast<int>(next_second - now_second);
        int dif_m_second = static_cast<int>(next_m_second - now_m_second);
        dif_m_second = dif_m_second + (1000 * dif_second);
        dif_m_second = dif_m_second - counter_playback *PLAYBACK_TIMEOUT_MS;

        if(dif_m_second <= 15)
        {
            set_index(next_index);
            counter_playback = 0;
        }
        else
        {
            counter_playback+= 1;
        }
    }

}

void mainPage::start_livepaylack()
{
    if(live_playback_timer->isActive())
    {
        live_playback_timer->stop();
        ui->start_stop_button->setText("başlat");
    }
    else
    {
        ui->start_stop_button->setText("durdur");
        live_playback_timer->start();
    }
}