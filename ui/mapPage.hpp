

#ifndef MAPPAGE_HPP
#define MAPPAGE_HPP

#include <iostream>
#include <array>

#include <QMainWindow>
#include <QtWidgets>
#include <QTimer>
#include <QQuickItem>
#include <QQuickWidget>
#include <tlogParser.hpp>

namespace Ui {
    class mapWidget;
};
class mapPage :public QWidget
{
    Q_OBJECT
public:
    explicit mapPage(QWidget * parent = 0);
    ~mapPage() override;
    void setup_ui();
    void set_tlog_parser(tlogParser * ptr) {tlog_parser_ptr = ptr;}
private:
    Ui::mapWidget * ui = nullptr;
    tlogParser * tlog_parser_ptr;

signals:

public slots:
    void update_map_index(int index);
    void append_map_data();
    void set_index(int idex);

};
#endif