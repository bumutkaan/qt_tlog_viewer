

#ifndef LOGVIEWERPAGE_HPP
#define LOGVIEWERPAGE_HPP

#include <iostream>
#include <chrono>

#include <QMainWindow>
#include <QtWidgets>
#include <QTimer>

#include <tlogParser.hpp>


namespace Ui {
    class logViewerWidget;
};
class logViewerPage :public QWidget
{
    Q_OBJECT
public:
    explicit logViewerPage(QWidget * parent = 0);
    ~logViewerPage() override;
    void setup_ui();
    void set_tlog_parser(tlogParser* ptr) {tlog_parser_ptr = ptr;}
private:
    Ui::logViewerWidget * ui = nullptr;
    tlogParser * tlog_parser_ptr;

signals:
    void rowClicked(int row);
public slots:
    void append_log_data();
    void append_data_to_table(QString s1,QString s2,QString s3);
    void resize_table_columns();
    void set_index(int index);
};
#endif