#include "tlogParser.hpp"

#include <array>
#include <cstring>


std::vector<TelemetryData> tlogParser::m_data = std::vector<TelemetryData>();

tlogParser::tlogParser(QObject * parent) :
    parse_timer(new QTimer(this))
{
    parse_timer->setInterval(0);
    connect(parse_timer,&QTimer::timeout,this,&tlogParser::parse_yield);
}

tlogParser::~tlogParser()
{
    close();
}

bool tlogParser::open(const std::string& fileName)
{
    close();

    m_file.open(fileName, std::ios::binary);
    m_file.seekg(0, std::ios::end);
    std::streamsize fileSize = m_file.tellg();
    m_file.seekg(0, std::ios::beg);
    file_size = static_cast<std::uintmax_t>(fileSize);
    readed_size = 0;
    return m_file.is_open();
}

void tlogParser::close()
{
    if (m_file.is_open())
        m_file.close();
}

bool tlogParser::isOpen() const
{
    return m_file.is_open();
}

void tlogParser::parse()
{
    if (!m_file.is_open()) return;
    status = {};
    parse_timer->start();
}


void tlogParser::parse_yield()
{
    uint64_t timestamp = 0;

    if (!m_file.read(reinterpret_cast<char*>(&timestamp),sizeof(timestamp)))
    {
        parse_timer->stop();
        emit parseFinished(m_data.size());
    }

    bool messageReceived = false;

    while (!messageReceived)
    {
        uint8_t byte = 0;

        if (!m_file.read( reinterpret_cast<char*>(&byte), sizeof(byte)))
        {
            break;
        }
        mavlink_message_t message{};

        uint8_t result =
            mavlink_parse_char(
                MAVLINK_COMM_0,
                byte,
                &message,
                &status);

        if (result)
        {
            Packet packet;

            packet.timestamp = timestamp;
            packet.message = message;
            append_data(packet);

            messageReceived = true;
        }
    }

    std::streampos now_position = m_file.tellg();
    readed_size = static_cast<std::uintmax_t>(now_position);
    unsigned short readed_ratio = static_cast<unsigned short>((static_cast<double>(readed_size)/static_cast<double>(file_size)) * 100.0);
    emit readedData(readed_ratio);
}

void tlogParser::append_data(const tlogParser::Packet& packet)
{
    if (packet.message.msgid ==
        MAVLINK_MSG_ID_GLOBAL_POSITION_INT)
    {
        mavlink_global_position_int_t gps{};

        mavlink_msg_global_position_int_decode(
            &packet.message,
            &gps
            );

        TelemetryData data;

        data.m_second =  gps.time_boot_ms % 1000;
        data.second =  gps.time_boot_ms / 1000;

        data.latitude = static_cast<double>(gps.lat) / 1e7;

        data.longitude = static_cast<double>(gps.lon) / 1e7;

        data.altitude = static_cast<double>(gps.alt) / 1000.0;

        data.heading = static_cast<double>(gps.hdg) / 100.0;

        data.relative_alt = static_cast<double>(gps.relative_alt) / 100.0;

        data.vx = static_cast<double>(gps.vx) / 100.0;

        data.vy = static_cast<double>(gps.vy) / 100.0;

        data.vz = static_cast<double>(gps.vz) / 100.0;

        tlogParser::m_data.push_back(data);
        emit appendData();
    }
}
