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
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFileDialog>

#include "TcpSocket/tcpclient.h"
#include "Settings/customsettings.h"
#include "DataControl/datacontrol.h"
#include "FileIO/fileio.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum OpMode{ServoOnOff = 0, Initialize, Wait, JointMove, CartesianMove, PathTransfer};
    enum Servo{On=1,Off=0};
    enum Motion{JogMotion = 0, JointMotion, CartesianJogMotion, CartesianMotion};

private:
    Ui::MainWindow *ui;
    TcpClient *tcpClient;
    CustomSettings *customSettings;
    DataControl *dataControl;

    QStandardItemModel *model;
    QStandardItemModel *jointPathModel, *cartPathModel;
    QByteArray txData;
    int rowIndex;

    void componentEnable(bool enable);

    QVector<QLineEdit*> txtCmdRel, txtCmdAbs;
    void setTxtCommandClear();

    vector< vector<double> > jointPathTxtData, cartPathTxtData;

public slots:
    // button event
    void btnConnectClicked();
    void btnDisconnectClicked();
    void btnSetInitClicked();
    void btnServOnClicked();
    void btnServoOffClicked();
    void btnJogMoveClicked();
    void btnSetCommandClicked();
    void btnFileLoadClicked();
    void btnPathApplyClicked();
    void btnPathClearClicked();
    void btnPathInsertClicked();
    void btnPathDeleteClicked();
    void btnPathAppendClicked();

    // checkbox event
    void cbJointPathClicked();
    void cbCartesianPathClicked();

    // server event
    void onConnectServer();
    void disConnectServer();
    void readMessage();

    // tableview event
    void on_tvPathData_clicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
