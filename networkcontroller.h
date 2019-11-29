#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <qnetworkaccessmanager.h>
#include <qudpsocket.h>
#include <qnetworkdatagram.h>

#define type_t char

#define STANDARD_PORT 3500
#define FRAME_PAYLOAD_SIZE 72

#define NIN '0';
#define EOT '1'
#define DATA '2'
#define META '3'
#define INIT '4'
#define ACKWM '5' // TODO: This is defined by lowercase letters in the client code

struct type
{
    type_t  _type;
};

struct Header
{
    type    _type; // Allocates 1 bytes for type identification
    short     _src; // Allocates 2 bytes for source adress
    short     _dst; // Allocates 2 bytes for destination adress
    char    _protocol; // Allocates 1 byte for protocol identification

};

struct Data
{
    type    _type;
    char    _data[0];
};


union Raw_Frame
{
    char    _raw[FRAME_PAYLOAD_SIZE];

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

    void setPort(quint16 port);


signals:
    void state_changed(Formatted_Frame &frame);

private slots:
    void recieve();

private:

    void extractData(QNetworkDatagram dGram);

    QUdpSocket _socket;
    QList<QNetworkDatagram>_datagrams;

};

#endif // NETWORKCONTROLLER_H
