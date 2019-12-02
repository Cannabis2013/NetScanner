#include "networkcontroller.h"

NetworkController::NetworkController()
{
    _socket = new QUdpSocket(this);
    qRegisterMetaType<Formatted_Packet>("Formatted_Frame");
}

bool NetworkController::setPort(quint16 port)
{
    if(_socket->state() == QAbstractSocket::UnconnectedState)
        return _socket->bind(port);
    else
        return false;
}

bool NetworkController::startListening()
{
    connect(_socket,&QUdpSocket::readyRead,this,&NetworkController::recieve);
    return true;
}

void NetworkController::stopListening()
{
    _socket->disconnectFromHost();
    _socket->disconnect(_socket,&QUdpSocket::readyRead,this,&NetworkController::recieve);
}

void NetworkController::recieve()
{
    cout << "Something recieved" << endl;
    while (_socket->hasPendingDatagrams())
    {
        QNetworkDatagram dGram = _socket->receiveDatagram(128);
        extractData(dGram);
    }
}

void NetworkController::copyArray(char *dst, char *src, uint len)
{
    for (uint i = 0; i < len; ++i)
        *(dst + i) = *(src + i);
}

void NetworkController::extractData(QNetworkDatagram dGram)
{
    Frame_PTU frame;

    Formatted_Packet f_frame;
    char* data = dGram.data().data();
    copyArray(frame.raw,data,FRAME_PAYLOAD_SIZE);

    Raw_Packet f;
    copyArray(f.raw,frame.frame.payload,FRAME_PAYLOAD_SIZE);

    if(f._header.type._type == INIT)
    {
        f_frame.type = "Initial frame";

        f_frame.src_adrs = QString::number(f._header.src);
        f_frame.dst_adrs = QString::number(f._header.dst);

        f_frame.protocol = (f._header.protocol == 1) ? "UDP" : "Unknown";
    }
    else if (f._header.type._type == ACKWM) {
        f_frame.type = "acknowledgement frame";

        QHostAddress source_adress(static_cast<quint32>(f._header.src));
        QHostAddress destination_adress(static_cast<quint32>(f._header.dst));
        f_frame.src_adrs = source_adress.toString();
        f_frame.dst_adrs = destination_adress.toString();

        f_frame.protocol = (f._header.protocol == 1) ? "UDP" : "Unknown";
    }
    else if (f._data._type._type == CHUNK) {
        f_frame.data = f._data._data;
    }

    emit state_changed(f_frame);
}

bool NetworkController::isListening() const
{
    return _isListening;
}
