#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qdatetime.h>
#include <qlineedit.h>
#include <qtreewidget.h>
#include <QTreeWidgetItem>
#include <qcombobox.h>
#include "networkcontroller.h"
#include <qtextbrowser.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define STANDARD_PORT 45000

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

    void on_pushButton_2_clicked();

    void on_TypeSelector_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    QString currentPort;

    NetworkController *nCon;

    QTextBrowser *msgBrowser;
    QTreeWidget *treeWidget;
    QLineEdit *inboundPortSelector,*outboundPortSelector;
    QComboBox *typeBox;
};
#endif // MAINWINDOW_H
