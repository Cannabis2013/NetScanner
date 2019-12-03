#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow()
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    nCon = new NetworkController();
    treeWidget = ui->treeWidget;
    inboundPortSelector = ui->lineEdit;
    outboundPortSelector = ui->lineEdit_2;
    typeBox = ui->TypeSelector;
    msgBrowser = ui->messageSelector;

    connect(nCon,&NetworkController::state_changed,this,&MainWindow::appendData);

    nCon->setPort(STANDARD_PORT);
    inboundPortSelector->setText(QString::number(STANDARD_PORT));
    on_start_but_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::appendData(Formatted_Packet &f_frame)
{

    QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()
                                                << f_frame.type
                                                << f_frame.src_adrs
                                                << f_frame.dst_adrs
                                                << f_frame.data
                                                << f_frame.descr
                                                << QDateTime::currentDateTime().toString());
    treeWidget->addTopLevelItem(item);
}

void MainWindow::on_lineEdit_returnPressed()
{
    on_stop_but_clicked();
    quint16 port = static_cast<quint16>(inboundPortSelector->text().toInt());
    if(!nCon->setPort(port))
    {
        inboundPortSelector->setText(currentPort);
        on_start_but_clicked();
        return;
    }
    on_start_but_clicked();

}

void MainWindow::on_start_but_clicked()
{
    currentPort = inboundPortSelector->text();
    nCon->startListening();
    ui->start_but->setText("Is listening");
    ui->start_but->setEnabled(false);
    ui->stop_but->setEnabled(true);
}

void MainWindow::on_stop_but_clicked()
{
    nCon->stopListening();
    ui->stop_but->setEnabled(false);
    ui->start_but->setText("Start listening");
    ui->start_but->setEnabled(true);
}

void MainWindow::on_pushButton_2_clicked()
{
    Frame_PTU frame;
    frame.frame.header.dst = outboundPortSelector->text().toUShort();

    if(typeBox->currentText() == "INIT")
    {
        Packet packet;
        packet.header.type.type = INIT;
        packet.header.dst = outboundPortSelector->text().toUShort();
        NetworkController::copyArray(frame.frame.payload,packet.raw,FRAME_PAYLOAD_SIZE + ADDITIONAL_OVERHEAD);
    }
    else if(typeBox->currentText() == "META")
    {
        Packet packet;
        packet.header.type.type = META;
        packet.header.dst = outboundPortSelector->text().toUShort();
        NetworkController::copyArray(frame.frame.payload,packet.raw,FRAME_PAYLOAD_SIZE + ADDITIONAL_OVERHEAD);
    }

    NetworkController::sendFrame(frame,outboundPortSelector->text().toUShort());
}

void MainWindow::on_TypeSelector_currentIndexChanged(const QString &arg1)
{

}
