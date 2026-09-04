

#ifndef MAINPAGE_HPP
#define MAINPAGE_HPP

#include <iostream>
#include <array>

#include <QMainWindow>
#include <QtWidgets>
#include <QTimer>

#include "logViewerPage.hpp"
#include "mapPage.hpp"
#include <tlogParser.hpp>

namespace Ui {
    class mainWidget;
};
class mainPage :public QWidget
{
    Q_OBJECT
public:
    explicit mainPage(QWidget * parent = 0);
    ~mainPage() override;
    void setup_ui();
    void setup_signal_slots();
    void set_tlog_parser(tlogParser *  ptr);
private:
    Ui::mainWidget * ui = nullptr;
    logViewerPage * log_viewer_page_ptr;
    mapPage * map_page_ptr;
    tlogParser * tlog_parser_ptr;
    QTimer * live_playback_timer;

signals:

public slots:
    void load_map_page();
    void load_data_view_page();
    void set_slider_max_data(int data_size);
    void set_index(int index);
    void append_data();
    void resize_event();

    void slider_position_changed(int value);
    void live_playback_func();
    void start_livepaylack();

};
#endif