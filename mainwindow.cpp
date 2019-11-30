#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow()
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    nCon = new NetworkController();
    treeWidget = ui->treeWidget;
    portSelector = ui->lineEdit;

    connect(nCon,&NetworkController::state_changed,this,&MainWindow::appendData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::appendData(Formatted_Frame &f_frame)
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
    quint16 port = static_cast<quint16>(portSelector->text().toInt());
    nCon->setPort(port);
    on_start_but_clicked();

}

void MainWindow::on_start_but_clicked()
{
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
