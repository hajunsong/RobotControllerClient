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

    connect(ui->btnSetInit, SIGNAL(clicked()), this, SLOT(btnSetInitClicked()));

    dataControl = new DataControl();

    connect(ui->btnServoOn, SIGNAL(clicked()), this, SLOT(btnServOnClicked()));
    connect(ui->btnServoOff, SIGNAL(clicked()), this, SLOT(btnServoOffClicked()));

    connect(ui->btnJ1N, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnJ1P, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnJ2N, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnJ2P, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnJ3N, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnJ3P, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnJ4N, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnJ4P, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnJ5N, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnJ5P, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnJ6N, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnJ6P, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));

    txtCmdAbs.push_back(ui->txtJCmdAbs1);
    txtCmdAbs.push_back(ui->txtJCmdAbs2);
    txtCmdAbs.push_back(ui->txtJCmdAbs3);
    txtCmdAbs.push_back(ui->txtJCmdAbs4);
    txtCmdAbs.push_back(ui->txtJCmdAbs5);
    txtCmdAbs.push_back(ui->txtJCmdAbs6);
    txtCmdAbs.push_back(ui->txtCCmdAbs1);
    txtCmdAbs.push_back(ui->txtCCmdAbs2);
    txtCmdAbs.push_back(ui->txtCCmdAbs3);
    txtCmdAbs.push_back(ui->txtCCmdAbs4);
    txtCmdAbs.push_back(ui->txtCCmdAbs5);
    txtCmdAbs.push_back(ui->txtCCmdAbs6);
    txtCmdRel.push_back(ui->txtJCmdRel1);
    txtCmdRel.push_back(ui->txtJCmdRel2);
    txtCmdRel.push_back(ui->txtJCmdRel3);
    txtCmdRel.push_back(ui->txtJCmdRel4);
    txtCmdRel.push_back(ui->txtJCmdRel5);
    txtCmdRel.push_back(ui->txtJCmdRel6);
    txtCmdRel.push_back(ui->txtCCmdRel1);
    txtCmdRel.push_back(ui->txtCCmdRel2);
    txtCmdRel.push_back(ui->txtCCmdRel3);
    txtCmdRel.push_back(ui->txtCCmdRel4);
    txtCmdRel.push_back(ui->txtCCmdRel5);
    txtCmdRel.push_back(ui->txtCCmdRel6);
    for(int i = 0; i < txtCmdRel.length(); i++)
    {
        txtCmdRel[i]->setText("0");
    }
    for(int i = 0; i < txtCmdAbs.length(); i++)
    {
        txtCmdAbs[i]->setText("0");
    }

    connect(ui->btnJSet1, SIGNAL(clicked()), this, SLOT(btnSetCommandClicked()));
    connect(ui->btnJSet2, SIGNAL(clicked()), this, SLOT(btnSetCommandClicked()));
    connect(ui->btnJSet3, SIGNAL(clicked()), this, SLOT(btnSetCommandClicked()));
    connect(ui->btnJSet4, SIGNAL(clicked()), this, SLOT(btnSetCommandClicked()));
    connect(ui->btnJSet5, SIGNAL(clicked()), this, SLOT(btnSetCommandClicked()));
    connect(ui->btnJSet6, SIGNAL(clicked()), this, SLOT(btnSetCommandClicked()));

    connect(ui->btnCSet1, SIGNAL(clicked()), this, SLOT(btnSetCommandClicked()));
    connect(ui->btnCSet2, SIGNAL(clicked()), this, SLOT(btnSetCommandClicked()));
    connect(ui->btnCSet3, SIGNAL(clicked()), this, SLOT(btnSetCommandClicked()));
    connect(ui->btnCSet4, SIGNAL(clicked()), this, SLOT(btnSetCommandClicked()));
    connect(ui->btnCSet5, SIGNAL(clicked()), this, SLOT(btnSetCommandClicked()));
    connect(ui->btnCSet6, SIGNAL(clicked()), this, SLOT(btnSetCommandClicked()));

    connect(ui->btnC1N, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnC2N, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnC3N, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnC4N, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnC5N, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnC6N, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnC1P, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnC2P, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnC3P, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnC4P, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnC5P, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));
    connect(ui->btnC6P, SIGNAL(clicked()), this, SLOT(btnJogMoveClicked()));

    connect(ui->cbJointPath, SIGNAL(clicked()), this, SLOT(cbJointPathClicked()));
    connect(ui->cbCartesianPath, SIGNAL(clicked()), this, SLOT(cbCartesianPathClicked()));

    connect(ui->btnFileLoad, SIGNAL(clicked()), this, SLOT(btnFileLoadClicked()));
    connect(ui->btnPathClear, SIGNAL(clicked()), this, SLOT(btnPathClearClicked()));
    connect(ui->btnPathApply, SIGNAL(clicked()), this, SLOT(btnPathApplyClicked()));
    connect(ui->btnPathInsert, SIGNAL(clicked()), this, SLOT(btnPathInsertClicked()));
    connect(ui->btnPathDelete, SIGNAL(clicked()), this, SLOT(btnPathDeleteClicked()));

    jointPathModel = new QStandardItemModel(1, NUM_JOINT, this);
    cartPathModel = new QStandardItemModel(1, NUM_DOF, this);

    ui->txtNumJoint->setText(QString::number(NUM_JOINT));
    ui->txtNumDof->setText(QString::number(NUM_DOF));
    ui->txtModuleType->setText(MODULE_TYPE == 1 ? "FAR" : MODULE_TYPE == 2 ? "SEA" : "JS-R8");
    ui->txtCommType->setText(COMM_TYPE == 1 ? "RS485" : "RS232");

    customSettings = new CustomSettings(ui);
    customSettings->loadConfigFile();
}

MainWindow::~MainWindow()
{
    customSettings->saveConfigFile();
    txtCmdRel.clear();
    txtCmdAbs.clear();
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
//    ui->btnSetInit->setEnabled(false);
    ui->gbRobotConfig->setEnabled(false);
    componentEnable(false);
    tcpClient->socket->close();
    qDebug() << "Disconnected Server";
}
void MainWindow::btnSetInitClicked()
{
    txData.clear();
    txData.append(Qt::Key_N);
    txData.append(Qt::Key_D);
    txData.append(NUM_JOINT);
    txData.append(NUM_DOF);
    txData.append(MODULE_TYPE);
    txData.append(Qt::Key_N);
    txData.append(Qt::Key_E);

    qDebug() << "txData : " << txData;

    tcpClient->socket->write(txData);

    int row = 2;
    model = new QStandardItemModel(row, NUM_JOINT, this);
    ui->tvRobotInfor->setModel(model);

    for(int i = 0; i < row; i++){
        for(int j = 0; j < NUM_JOINT; j++){
            QModelIndex index = model->index(i, j, QModelIndex());
            model->setData(index, 0);
        }
    }

    QStringList vHeader;
    vHeader.append("Pos [deg]");
    vHeader.append("Pose [mm, deg]");
    model->setVerticalHeaderLabels(vHeader);
}

void MainWindow::btnServOnClicked()
{
    dataControl->ClientToServer.opMode = OpMode::ServoOnOff;
    dataControl->ClientToServer.subMode = Servo::On;
    memset(dataControl->ClientToServer.desiredJoint, 0, sizeof(double)*NUM_JOINT);
    memset(dataControl->ClientToServer.desiredCartesian, 0, sizeof(double)*NUM_DOF);

    txData.clear();
    txData.append(Qt::Key_N);
    txData.append(Qt::Key_S);
    txData.append(dataControl->ClientToServer.opMode);
    txData.append(dataControl->ClientToServer.subMode);
    for(int i = 0; i < NUM_JOINT; i++){
        txData.append(QByteArray::number(dataControl->ClientToServer.desiredJoint[i], 'f', 6));
    }
    for(int i = 0; i < NUM_DOF; i++){
        txData.append(QByteArray::number(dataControl->ClientToServer.desiredCartesian[i], 'f', 6));
    }
    txData.append(Qt::Key_N);
    txData.append(Qt::Key_E);


    qDebug() << "txData : " << txData;

    tcpClient->socket->write(txData);
}

void MainWindow::btnServoOffClicked()
{
    dataControl->ClientToServer.opMode = OpMode::ServoOnOff;
    dataControl->ClientToServer.subMode = Servo::Off;
    memset(dataControl->ClientToServer.desiredJoint, 0, sizeof(double)*NUM_JOINT);
    memset(dataControl->ClientToServer.desiredCartesian, 0, sizeof(double)*NUM_DOF);

    txData.clear();
    txData.append(Qt::Key_N);
    txData.append(Qt::Key_S);
    txData.append(dataControl->ClientToServer.opMode);
    txData.append(dataControl->ClientToServer.subMode);
    for(int i = 0; i < NUM_JOINT; i++){
        txData.append(QByteArray::number(dataControl->ClientToServer.desiredJoint[i], 'f', 6));
    }
    for(int i = 0; i < NUM_DOF; i++){
        txData.append(QByteArray::number(dataControl->ClientToServer.desiredCartesian[i], 'f', 6));
    }
    txData.append(Qt::Key_N);
    txData.append(Qt::Key_E);


    qDebug() << "txData : " << txData;

    tcpClient->socket->write(txData);
}

void MainWindow::btnJogMoveClicked()
{
    QString objName = sender()->objectName();
    QString moduleStr = objName.at(objName.length() - 2);
    int moduleIndex = moduleStr.toInt();
    QString PN = objName.at(objName.length() - 1);
    QString CJ = objName.at(3);

    dataControl->ClientToServer.opMode = CJ == "J" ? OpMode::JointMove : OpMode::CartesianMove;
    dataControl->ClientToServer.subMode = CJ == "J" ? Motion::JogMotion : Motion::CartesianJogMotion;
    memset(dataControl->ClientToServer.desiredJoint, 0, sizeof(double)*NUM_JOINT);
    memset(dataControl->ClientToServer.desiredCartesian, 0, sizeof(double)*NUM_DOF);

    txData.clear();
    txData.append(Qt::Key_N);
    txData.append(Qt::Key_S);
    txData.append(dataControl->ClientToServer.opMode);
    txData.append(dataControl->ClientToServer.subMode);
    for(int i = 0; i < NUM_JOINT; i++){
        if (CJ == "J"){
            if (i + 1 == moduleIndex){
                dataControl->ClientToServer.desiredJoint[i] = PN == "N" ? -5 : 5;
            }
        }
        txData.append(QByteArray::number(dataControl->ClientToServer.desiredJoint[i], 'f', 6));
    }
    for(int i = 0; i < NUM_DOF; i++){
        if (CJ == "C"){
            if (i + 1 == moduleIndex){
                if (i < 3){
                    dataControl->ClientToServer.desiredCartesian[i] = PN == "N" ? -10 : 10;
                }
                else{
                    dataControl->ClientToServer.desiredCartesian[i] = PN == "N" ? -5 : 5;
                }
            }
        }
        txData.append(QByteArray::number(dataControl->ClientToServer.desiredCartesian[i], 'f', 6));
    }
    txData.append(Qt::Key_N);
    txData.append(Qt::Key_E);

    qDebug() << "txData : " << txData;

    tcpClient->socket->write(txData);
}

void MainWindow::btnSetCommandClicked()
{
    QString objName = sender()->objectName();
    QString moduleStr = objName.at(objName.length() - 1);
    int moduleIndex = moduleStr.toInt();
    QString CJ = objName.at(3);
    int objIndex = -1;
    QString RA = nullptr;
    double value;

    if (CJ == "J"){
        objIndex = moduleIndex - 1;
    }
    else if(CJ == "C"){
        objIndex = moduleIndex + 6 - 1;
    }

    if (txtCmdRel[objIndex]->text().toInt() != 0  && txtCmdAbs[objIndex]->text().toInt() == 0){
        RA = "R";
    }
    else if (txtCmdRel[objIndex]->text().toInt() == 0  && txtCmdAbs[objIndex]->text().toInt() != 0){
        RA = "A";
    }

    dataControl->ClientToServer.opMode = CJ == "J" ? OpMode::JointMove : OpMode::CartesianMove;
    if (CJ == "J"){
        if (RA == "R"){
            dataControl->ClientToServer.subMode = Motion::JogMotion;
            value = txtCmdRel[objIndex]->text().toDouble();
        }
        else if (RA == "A"){
            dataControl->ClientToServer.subMode = Motion::JointMotion;
            value = txtCmdAbs[objIndex]->text().toDouble();
        }
    }
    else if (CJ == "C"){
        if (RA == "R"){
            dataControl->ClientToServer.subMode = Motion::CartesianJogMotion;
            value = txtCmdRel[objIndex]->text().toDouble();
        }
        else if (RA == "A"){
            dataControl->ClientToServer.subMode = Motion::CartesianMotion;
            value = txtCmdAbs[objIndex]->text().toDouble();
        }
    }
    memset(dataControl->ClientToServer.desiredJoint, 0, sizeof(double)*NUM_JOINT);
    memset(dataControl->ClientToServer.desiredCartesian, 0, sizeof(double)*NUM_DOF);

    txData.clear();
    txData.append(Qt::Key_N);
    txData.append(Qt::Key_S);
    txData.append(dataControl->ClientToServer.opMode);
    txData.append(dataControl->ClientToServer.subMode);
    for(int i = 0; i < NUM_JOINT; i++){
        if (CJ == "J"){
            if (i + 1 == moduleIndex){
                dataControl->ClientToServer.desiredJoint[i] = value;
            }
        }
        txData.append(QByteArray::number(dataControl->ClientToServer.desiredJoint[i], 'f', 6));
    }
    for(int i = 0; i < NUM_DOF; i++){
        if (CJ == "C"){
            if (i + 1 == moduleIndex){
                dataControl->ClientToServer.desiredCartesian[i] = value;
            }
        }
        txData.append(QByteArray::number(dataControl->ClientToServer.desiredCartesian[i], 'f', 6));
    }
    txData.append(Qt::Key_N);
    txData.append(Qt::Key_E);

    qDebug() << "txData : " << txData;

    tcpClient->socket->write(txData);

    setTxtCommandClear();
}

void MainWindow::onConnectServer(){
    qDebug() << "Connected Server";
    ui->btnConnect->setEnabled(false);
    ui->btnDisconnect->setEnabled(true);
//    ui->btnSetInit->setEnabled(true);
    ui->gbRobotConfig->setEnabled(true);
    tcpClient->socket->write("O");
}

void MainWindow::readMessage(){
    QByteArray rxData = tcpClient->socket->readAll();
//    qDebug() << "Data size : " << rxData.size();
//    qDebug() << rxData;

    size_t size = static_cast<size_t>(rxData.size());
    if (size == 1){
        if(rxData.at(0) == 'X'){
            qDebug() << "Client & Server configuration is difference";
            disConnectServer();
        }
        else if(rxData.at(0) == 'S'){
            qDebug() << "Client & Server configuration check complete";
            componentEnable(true);
        }
    }
    else if (size == SERVER_TO_CLIENT_LEN){
        char *pData = rxData.data();
        int indx = NRMK_SOCKET_TOKEN_SIZE;
        memcpy(&dataControl->ServerToClient, pData + indx, DATA_INDEX_LEN);
        indx += DATA_INDEX_LEN;
        memcpy(dataControl->ServerToClient.presentJointPosition, pData + indx, JOINT_POSITION_LEN*NUM_JOINT);
        indx += JOINT_POSITION_LEN*NUM_JOINT;
        memcpy(dataControl->ServerToClient.presentCartesianPose, pData + indx, CARTESIAN_POSE_LEN*NUM_DOF);
        indx += CARTESIAN_POSE_LEN*NUM_DOF;

        for(int i = 0; i < NUM_JOINT; i++){
            QModelIndex index = model->index(0, i);
            model->setData(index, dataControl->ServerToClient.presentJointPosition[i]);
            ui->tvRobotInfor->update(index);
        }

        for(int i = 0; i < NUM_JOINT; i++){
            QModelIndex index = model->index(1, i);
            model->setData(index, dataControl->ServerToClient.presentCartesianPose[i]);
            ui->tvRobotInfor->update(index);
        }
    }
}

void MainWindow::disConnectServer(){
    ui->btnDisconnect->animateClick();
}

void MainWindow::componentEnable(bool enable){
    ui->gbRobotInfor->setEnabled(enable);
    ui->gbServoControl->setEnabled(enable);
    ui->gbCartMoveCommand->setEnabled(enable);
    ui->gbJointMoveCommand->setEnabled(enable);
}

void MainWindow::setTxtCommandClear()
{
    for(int i = 0; i < txtCmdRel.length(); i++)
    {
        txtCmdRel[i]->setText("0");
    }
    for(int i = 0; i < txtCmdAbs.length(); i++)
    {
        txtCmdAbs[i]->setText("0");
    }
}

void MainWindow::cbJointPathClicked()
{
    ui->cbCartesianPath->setChecked(!ui->cbJointPath->isChecked());

    int row = 1;
    ui->tvPathData->setModel(jointPathModel);

    for(int i = 0; i < row; i++){
        for(int j = 0; j < NUM_JOINT; j++){
            QModelIndex index = jointPathModel->index(i, j, QModelIndex());
            jointPathModel->setData(index, 0);
        }
    }
}

void MainWindow::cbCartesianPathClicked()
{
    ui->cbJointPath->setChecked(!ui->cbCartesianPath->isChecked());

    int row = 1;
    ui->tvPathData->setModel(cartPathModel);

    for(int i = 0; i < row; i++){
        for(int j = 0; j < NUM_DOF; j++){
            QModelIndex index = cartPathModel->index(i, j, QModelIndex());
            cartPathModel->setData(index, 0);
        }
    }
}

void MainWindow::btnFileLoadClicked()
{

}

void MainWindow::btnPathApplyClicked()
{

}

void MainWindow::btnPathClearClicked()
{
    if (ui->cbJointPath->isChecked()){
        jointPathModel->clear();
    }
    else{
        cartPathModel->clear();
    }
}

void MainWindow::btnPathInsertClicked()
{
    if (ui->cbJointPath->isChecked()){
        jointPathModel->insertRow(1);
    }
    else{
        cartPathModel->insertRow(1);
    }
}

void MainWindow::btnPathDeleteClicked()
{
    if (ui->cbJointPath->isChecked()){
        jointPathModel->removeRows(jointPathModel->se, 1);
    }
    else{
    }
}

//for(int i = 0; i < NUM_JOINT; i++){
//    QModelIndex index = model->index(0, i);
//    model->setData(index, dataControl->ServerToClient.presentJointPosition[i]);
//    ui->tvRobotInfor->update(index);
//}
