#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <qnetworkaccessmanager.h>
#include <qudpsocket.h>
#include <qnetworkdatagram.h>
#include <iostream>

#include "structures.h"

using namespace std;



class NetworkController : public QObject
{
    Q_OBJECT
public:
    NetworkController();

    bool isListening() const;

    bool setPort(quint16 port);
    bool startListening();
    void stopListening();

    static qint64 sendFrame(Frame_PTU ptu, ushort port);

    static void copyArray(char *dst, char *src, uint len);

signals:
    void state_changed(Formatted_Packet &frame);

private slots:
    void recieve();

private:
    void extractData(QNetworkDatagram dGram);

    bool _isListening = false;
    QUdpSocket *_socket;
};

#endif // NETWORKCONTROLLER_H
