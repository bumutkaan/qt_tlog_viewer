

#ifndef FILESELECTPAGE_HPP
#define FILESELECTPAGE_HPP

#include <iostream>
#include <QMainWindow>
#include <QtWidgets>
#include <QTimer>
#include <QFileDialog>

#include <tlogParser.hpp>



namespace Ui {
class fileSelectWidget;
};
class fileSelectPage :public QWidget
{
    Q_OBJECT
public:
    explicit fileSelectPage(QWidget * parent = 0);
    ~fileSelectPage() override;
    void setup_ui();

    void set_tlog_parser(tlogParser * ptr) {tlog_parser_ptr = ptr;}
private:
    Ui::fileSelectWidget * ui = nullptr;
    QString fileUrl;
    tlogParser * tlog_parser_ptr;

signals:
    void appendData();
    void fileLoaded(int data_size);

public slots:
    void selectFile();
    void readedRatio(unsigned short readed_ratio);
};
#endif