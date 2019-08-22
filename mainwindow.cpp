#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnConnect, SIGNAL(clicked()), this, SLOT(btnConnectClicked()));
    connect(ui->btnDisconnect, SIGNAL(clicked()), this, SLOT(btnDisconnectClicked()));

    tcpClient = new TcpClient();
    connect(tcpClient->socket, SIGNAL(connected()), this, SLOT(onConnectServer()));
    connect(tcpClient->socket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpClient->socket, SIGNAL(disconnected()), this, SLOT(disConnectServer()));

    ui->btnDisconnect->setEnabled(false);
    ui->btnSetInit->setEnabled(false);

    connect(ui->cbNumJoint, SIGNAL(currentIndexChanged(int)), this, SLOT(cbInitParamChanaged(int)));
    connect(ui->cbNumDof, SIGNAL(currentIndexChanged(int)), this, SLOT(cbInitParamChanaged(int)));
    connect(ui->cbModuleType, SIGNAL(currentIndexChanged(int)), this, SLOT(cbInitParamChanaged(int)));
    connect(ui->cbCommType, SIGNAL(currentIndexChanged(int)), this, SLOT(cbInitParamChanaged(int)));

    connect(ui->btnSetInit, SIGNAL(clicked()), this, SLOT(btnSetInitClicked()));

    dataControl = new DataControl();

    customSettings = new CustomSettings(ui);
    customSettings->loadConfigFile();
}

MainWindow::~MainWindow()
{
    customSettings->saveConfigFile();
    delete ui;
    delete tcpClient;
    delete dataControl;
}

void MainWindow::btnConnectClicked(){
    tcpClient->setIpAddress(ui->txtIP->text());
    tcpClient->setPort(ui->txtPORT->text().toUShort());
    emit tcpClient->connectToServer();
}

void MainWindow::btnDisconnectClicked(){
    ui->btnConnect->setEnabled(true);
    ui->btnDisconnect->setEnabled(false);
    ui->btnSetInit->setEnabled(false);
    tcpClient->socket->close();
    qDebug() << "Disconnected Server";
}
void MainWindow::btnSetInitClicked()
{
    QByteArray txData;
    txData.clear();
    txData.append(Qt::Key_N);
    txData.append(Qt::Key_D);
    txData.append(dataControl->ClientToServerInitParam.numJoint);
    txData.append(dataControl->ClientToServerInitParam.numDof);
    txData.append(dataControl->ClientToServerInitParam.module);
    txData.append(Qt::Key_N);
    txData.append(Qt::Key_E);

    tcpClient->socket->write(txData);

    dataControl->ClientToServer.desiredJoint = new double[dataControl->ClientToServerInitParam.numJoint];
    dataControl->ClientToServer.desiredCartesian = new double[dataControl->ClientToServerInitParam.numDof];
    dataControl->ServerToClient.presentJoint = new int[dataControl->ClientToServerInitParam.numJoint];

    int row = 1;
    int col = ui->cbNumJoint->currentText().toInt();
    model = new QStandardItemModel(row, col, this);

    ui->tvRobotInfor->setModel(model);

    // Generate data
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            QModelIndex index = model->index(i, j, QModelIndex());
            model->setData(index, 1);
        }
    }
}

void MainWindow::onConnectServer(){
    qDebug() << "Connected Server";
    ui->btnConnect->setEnabled(false);
    ui->btnDisconnect->setEnabled(true);
    ui->btnSetInit->setEnabled(true);
    tcpClient->socket->write("O");
}

void MainWindow::readMessage(){
    QByteArray rxData = tcpClient->socket->readAll();
    qDebug() << "Data size : " << rxData.size();

    size_t size = static_cast<size_t>(rxData.size());
    if (size == 29){
        char *pData = rxData.data();
        memcpy(&dataControl->ServerToClient, pData + 2, 1);
        memcpy(dataControl->ServerToClient.presentJoint, pData + 3, 48);

        qDebug() << "data index : " << dataControl->ServerToClient.data_index;
        qDebug() << "present position 0 : " << dataControl->ServerToClient.presentJoint[0];
        qDebug() << "present position 1 : " << dataControl->ServerToClient.presentJoint[1];
        qDebug() << "present position 2 : " << dataControl->ServerToClient.presentJoint[2];
        qDebug() << "present position 3 : " << dataControl->ServerToClient.presentJoint[3];
        qDebug() << "present position 4 : " << dataControl->ServerToClient.presentJoint[4];
        qDebug() << "present position 5 : " << dataControl->ServerToClient.presentJoint[5];
    }
}

void MainWindow::disConnectServer(){
    ui->btnDisconnect->animateClick();
}

void MainWindow::cbInitParamChanaged(int)
{
    QString objName = sender()->objectName();
    if (objName.contains("NumJoint")){
        dataControl->ClientToServerInitParam.numJoint = static_cast<char>(ui->cbNumJoint->currentText().toInt());
    }
    else if(objName.contains("NumDof")){
        dataControl->ClientToServerInitParam.numDof = static_cast<char>(ui->cbNumDof->currentText().toInt());
    }
    else if (objName.contains("Module")){
        dataControl->ClientToServerInitParam.module = static_cast<char>(ui->cbModuleType->currentIndex());
        if (ui->cbModuleType->currentText().contains("FAR") || ui->cbModuleType->currentText().contains("SEA")){
            ui->cbCommType->setEnabled(false);
            ui->labelCommType->setEnabled(false);
            ui->cbCommType->setCurrentIndex(1);
        }
        else{
            ui->cbCommType->setEnabled(true);
            ui->labelCommType->setEnabled(true);
        }
    }
//    else if(objName.contains("Comm")){
//        if (ui->cbCommType->currentText().contains("Ether")){
//            ui->cbBaudRate->hide();
//            ui->labelBaudRate->hide();
//        }
//        else{
//            ui->cbBaudRate->setHidden(false);
//            ui->labelBaudRate->setHidden(false);
//        }
//    }
}
