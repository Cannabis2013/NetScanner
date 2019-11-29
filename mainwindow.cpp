#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(IApplicationInterface *interface)
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

