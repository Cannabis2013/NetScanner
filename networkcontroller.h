#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <qnetworkaccessmanager.h>
#include <qudpsocket.h>
#include <qnetworkdatagram.h>
#include <iostream>

using namespace std;

#define type_t char

#define STANDARD_PORT 45000
#define FRAME_PAYLOAD_SIZE 128

#define CHUNK '0'
#define META '1'
#define INIT '2'
#define ACKWM '3'
#define P_ACKWM '4'
#define LAST_CHUNK '5'

struct Type
{
    type_t  _type;
};

struct Header
{
    Type    type; // Allocates 1 bytes for type identification
    ushort   src; // Allocates 2 bytes for source adress
    ushort   dst; // Allocates 2 bytes for destination adress
    char    protocol; // Allocates 1 byte for protocol identification
    unsigned int magic_key; // Allocates 4 byres for unique identification

};

struct Data
{
    Type    _type;
    char    _data[0];
};


union Raw_Packet
{
    char    raw[FRAME_PAYLOAD_SIZE];
    Header  _header;
    Data    _data;
};

struct Formatted_Packet
{
    QString src_adrs;
    QString dst_adrs;
    QString data;
    QString type;
    QString descr;
    QString protocol;
};

typedef struct
{
    ushort src; // 2 bytes allocated
    ushort dst; // 2 bytes allocated
    u_int8_t lenght; // 1 bytes allocated
    u_int8_t protocol; // 1 bytes allocated
}Frame_Header; // 6 bytes total allocated for this structure

typedef struct
{
    char            preAmble[10]; // 10 bytes allocated
    uint            unique_adress; // 4 bytes allocated
    Frame_Header    header; // 6 bytes allocated
    char            payload[128]; // 128 bytes allocated
    ushort          checksum; // 2 bytes allocated

}Frame; // 10 + 4 + 6 + 128 + 2 = 150 bytes total allocated for this structure

typedef union
{
    char    raw[150];
    Frame   frame; // 150 bytes allocated

}Frame_PTU;


class NetworkController : public QObject
{
    Q_OBJECT
public:
    NetworkController();

    bool isListening() const;

    bool setPort(quint16 port);
    bool startListening();
    void stopListening();

signals:
    void state_changed(Formatted_Packet &frame);

private slots:
    void recieve();

private:
    void copyArray(char *dst, char *src, uint len);
    void extractData(QNetworkDatagram dGram);

    bool _isListening = false;
    QUdpSocket *_socket;
};

#endif // NETWORKCONTROLLER_H
