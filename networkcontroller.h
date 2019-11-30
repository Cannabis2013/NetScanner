#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <qnetworkaccessmanager.h>
#include <qudpsocket.h>
#include <qnetworkdatagram.h>
#include <iostream>

using namespace std;

#define type_t char

#define STANDARD_PORT 3500
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


union Raw_Frame
{
    char    raw[FRAME_PAYLOAD_SIZE];
    Header  _header;
    Data    _data;
};

struct Formatted_Frame
{
    QString src_adrs;
    QString dst_adrs;
    QString data;
    QString type;
    QString descr;
    QString protocol;
};

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
    void state_changed(Formatted_Frame &frame);

private slots:
    void recieve();

private:
    void copyArray(char *dst, char *src, uint len);
    void extractData(QNetworkDatagram dGram);

    bool _isListening = false;
    QUdpSocket *_socket;
};

#endif // NETWORKCONTROLLER_H
