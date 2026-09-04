

#include "ui/ui_fileSelectWidget.h"
#include "fileSelectPage.hpp"

fileSelectPage::fileSelectPage(QWidget * parent) :
    ui(new Ui::fileSelectWidget)
{

}
fileSelectPage::~fileSelectPage(){
    delete ui;
}
void fileSelectPage::setup_ui(){
    ui->setupUi(this);
    ui->loading_label->hide();

    connect(ui->file_select_button,&QPushButton::clicked,this,&fileSelectPage::selectFile);
    connect(tlog_parser_ptr,&tlogParser::parseFinished,[this](int size){ emit fileLoaded(size); });
    connect(tlog_parser_ptr,&tlogParser::appendData,[this]() {emit appendData();});
    connect(tlog_parser_ptr,&tlogParser::readedData,this,&fileSelectPage::readedRatio);

}

void fileSelectPage::selectFile()
{
    fileUrl = QFileDialog::getOpenFileName(this,tr("TLOG dosyasi aç"), ".");

    if (!tlog_parser_ptr->open(fileUrl.toStdString()))
    {
        std::cout << "TLog acilamadi\n" << std::endl;
    }
    tlogParser::m_data.clear();
    ui->loading_label->setText("yükleniyor: 0%");
    ui->loading_label->show();
    ui->file_select_button->hide();
    tlog_parser_ptr->parse();

}

void fileSelectPage::readedRatio(unsigned short readed_ratio)
{
    QString str = QString::fromStdString("yükleniyor: "+std::to_string(readed_ratio)+"%");
    ui->loading_label->setText(str);

}