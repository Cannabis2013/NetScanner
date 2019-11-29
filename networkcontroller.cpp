#include "networkcontroller.h"

NetworkController::NetworkController()
{
    _socket.bind(QHostAddress::LocalHost,STANDARD_PORT);
    connect(&_socket,&QUdpSocket::readyRead,this,&NetworkController::recieve);

    qRegisterMetaType<Formatted_Frame>("Formatted_Frame");
}

void NetworkController::setPort(quint16 port)
{
    _socket.bind(QHostAddress::LocalHost,port);
}

void NetworkController::recieve()
{
    while (_socket.hasPendingDatagrams())
    {
        QNetworkDatagram dGram = _socket.receiveDatagram();
        _datagrams << dGram;
        extractData(dGram);
    }

}

void NetworkController::extractData(QNetworkDatagram dGram)
{
    Raw_Frame f;

    Formatted_Frame f_frame;
    char *data = dGram.data().data();

    strcpy(f._raw,data);

    if(f._header._type._type == INIT)
    {
        f_frame.type = "Initial frame";

        QHostAddress source_adress(static_cast<quint32>(f._header._src));
        QHostAddress destination_adress(static_cast<quint32>(f._header._dst));
        f_frame.src_adrs = source_adress.toString();
        f_frame.dst_adrs = destination_adress.toString();

        f_frame.protocol = (f._header._protocol == 1) ? "UDP" : "Unknown";
    }
    else if (f._header._type._type == ACKWM) {
        f_frame.type = "acknowledgement frame";

        QHostAddress source_adress(static_cast<quint32>(f._header._src));
        QHostAddress destination_adress(static_cast<quint32>(f._header._dst));
        f_frame.src_adrs = source_adress.toString();
        f_frame.dst_adrs = destination_adress.toString();

        f_frame.protocol = (f._header._protocol == 1) ? "UDP" : "Unknown";
    }
    else if (f._data._type._type == DATA) {
        f_frame.data = f._data._data;
    }

    emit state_changed(f_frame);
}
