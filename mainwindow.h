#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qdatetime.h>
#include <qlineedit.h>
#include <qtreewidget.h>
#include <QTreeWidgetItem>
#include "networkcontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private slots:
    void appendData(Formatted_Packet &f_frame);
    void on_lineEdit_returnPressed();

    void on_start_but_clicked();
    void on_stop_but_clicked();

private:
    Ui::MainWindow *ui;

    QString currentPort;

    NetworkController *nCon;
    QTreeWidget *treeWidget;
    QLineEdit *portSelector;
};
#endif // MAINWINDOW_H
