#include "ui/ui_mainWindow.h"
#include "window.hpp"


Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow),
    tlog_parser(new tlogParser(this))
{

}

Window::~Window()
{
    delete ui;
}

void Window::setup_ui(){
    ui->setupUi(this);
    
    // fileSelectPage * file_select_page_ptr;
    // mapPage * map_page_ptr;
    // logViewerPage * log_viewer_page_ptr;

    file_select_page_ptr = new fileSelectPage(this);
    file_select_page_ptr->set_tlog_parser(tlog_parser);
    file_select_page_ptr->setup_ui();

    ui->stackedWidget->addWidget(file_select_page_ptr);

    main_page_ptr = new mainPage(this);
     main_page_ptr->set_tlog_parser(tlog_parser);
    main_page_ptr->setup_ui();

    ui->stackedWidget->addWidget(main_page_ptr);

    setup_signal_slots();
    
    show_file_select_page();
}

void Window::setup_signal_slots()
{
    connect(file_select_page_ptr,&fileSelectPage::appendData,main_page_ptr,&mainPage::append_data);
    connect(file_select_page_ptr,&fileSelectPage::fileLoaded,this,&Window::show_main_page);

}

void Window::show_file_select_page()
{
     ui->stackedWidget->setCurrentWidget(file_select_page_ptr);
}

void Window::show_main_page(int data_size)
{
    main_page_ptr->set_slider_max_data(data_size);
    ui->stackedWidget->setCurrentWidget(main_page_ptr);
}

void Window::resizeEvent(QResizeEvent *event)
{
    main_page_ptr->resize_event();
}





