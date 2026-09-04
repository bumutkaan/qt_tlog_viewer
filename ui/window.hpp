#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <memory>
#include <vector>

#include <QMainWindow>
#include <QtWidgets>
#include <QTimer> 
#include <QKeyEvent>

#include "fileSelectPage.hpp"
#include "mainPage.hpp"

#include <tlogParser.hpp>

namespace Ui {
	class mainWindow;
}


class Window : public QMainWindow
{

    Q_OBJECT

public:

	explicit Window(QWidget *parent = 0);
    ~Window() override;

	void setup_ui();
    void setup_signal_slots(); // mutlaka setup_ui içinde veya sonrasında cagırılmalıdır.

private:

    Ui::mainWindow * ui = nullptr;

    fileSelectPage * file_select_page_ptr;
    mainPage * main_page_ptr;
    tlogParser * tlog_parser;

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:
  

public slots:
    void show_file_select_page();
    void show_main_page(int data_size);

    
};
#endif
