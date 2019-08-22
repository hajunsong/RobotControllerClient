#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSettings>
#include <QFile>
#include <QDesktopServices>
#include <QDir>
#include <QWidget>
#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>

#include "TcpSocket/tcpclient.h"
#include "Settings/customsettings.h"
#include "DataControl/datacontrol.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TcpClient *tcpClient;
    CustomSettings *customSettings;
    QStandardItemModel *model;
    DataControl *dataControl;

public slots:
    // button event
    void btnConnectClicked();
    void btnDisconnectClicked();
    void btnSetInitClicked();

    // server event
    void onConnectServer();
    void disConnectServer();
    void readMessage();

    // combo box event
    void cbInitParamChanaged(int);
};

#endif // MAINWINDOW_H
