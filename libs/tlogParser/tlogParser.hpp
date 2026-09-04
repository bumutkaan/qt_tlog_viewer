#pragma once

#include <cstdint>
#include <fstream>
#include <functional>
#include <string>
#include <iostream>

#include <QObject>
#include <QTimer>

extern "C" {
#include "../mavlink/common/mavlink.h"
}

// https://github.com/flocked-agriculture/mavlink_log/blob/main/docs/tlog_file_format.md
// https://mavlink.io/en/guide/serialization.html
// https://mavlink.io/en/guide/serialization.html#payload
// https://mavlink.io/en/mavgen_c/
// https://github.com/mavlink/c_library_v2

// https://docs.qgroundcontrol.com/master/en/qgc-dev-guide/file_formats/mavlink.html
struct TelemetryData
{

    unsigned int m_second = 0;
    unsigned int second = 0;

    double latitude = 0.0;
    double longitude = 0.0;
    double altitude = 0.0;
    double relative_alt = 0.0;
    double heading = 0.0;
    double speed = 0.0;
    double vx = 0.0;
    double vy= 0.0;
    double vz = 0.0;

};

class tlogParser : public QObject
{
    Q_OBJECT
public:
    struct Packet
    {
        uint64_t timestamp;
        mavlink_message_t message;
    };

    explicit tlogParser(QObject *parent = nullptr);
    ~tlogParser();

    bool open(const std::string& fileName);
    void close();

    void parse();


    bool isOpen() const;

    static std::vector<TelemetryData> m_data;

private:
    std::ifstream m_file;
    std::uintmax_t file_size;
    std::uintmax_t readed_size;
    mavlink_status_t status{};
    QTimer * parse_timer;

signals:
    void appendData();
    void parseFinished(int data_size);
    void readedData(unsigned short readed_ratio);

public slots:
    void append_data(const tlogParser::Packet& packet);
    void parse_yield();

};