#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customsettings.h"

CustomSettings::CustomSettings(void *_ui)
{
    ui = static_cast<Ui::MainWindow*>(_ui);
}

void CustomSettings::saveConfigFile()
{
    QSettings settings(configFile(), QSettings::IniFormat);

    QString ip = static_cast<Ui::MainWindow*>(ui)->txtIP->text();
    QString port = static_cast<Ui::MainWindow*>(ui)->txtPORT->text();
    int joint = static_cast<Ui::MainWindow*>(ui)->cbNumJoint->currentIndex();
    int dof = static_cast<Ui::MainWindow*>(ui)->cbNumDof->currentIndex();
    int module = static_cast<Ui::MainWindow*>(ui)->cbModuleType->currentIndex();
    int comm = static_cast<Ui::MainWindow*>(ui)->cbCommType->currentIndex();
//    int baud = static_cast<Ui::MainWindow*>(ui)->cbBaudRate->currentIndex();

    settings.setValue("IP", ip);
    settings.setValue("PORT", port);
    settings.setValue("NumJoint", joint);
    settings.setValue("NumDOF", dof);
    settings.setValue("ModuleType", module);
    settings.setValue("CommType", comm);
//    settings.setValue("BaudRate", baud);
    settings.sync();
}

void CustomSettings::loadConfigFile()
{
    if (!QFile::exists(configFile())) return;

    QSettings settings(configFile(), QSettings::IniFormat);

    QString ip = settings.value("IP").toString();
    QString port = settings.value("PORT").toString();
    int joint = settings.value("NumJoint").toInt();
    int dof = settings.value("NumDOF").toInt();
    int module = settings.value("ModuleType").toInt();
    int comm = settings.value("CommType").toInt();
//    int baud = settings.value("BaudRate").toInt();

    static_cast<Ui::MainWindow*>(ui)->txtIP->setText(ip);
    static_cast<Ui::MainWindow*>(ui)->txtPORT->setText(port);
    static_cast<Ui::MainWindow*>(ui)->cbNumJoint->setCurrentIndex(joint);
    static_cast<Ui::MainWindow*>(ui)->cbNumDof->setCurrentIndex(dof);
    static_cast<Ui::MainWindow*>(ui)->cbModuleType->setCurrentIndex(module);
    static_cast<Ui::MainWindow*>(ui)->cbCommType->setCurrentIndex(comm);
//    static_cast<Ui::MainWindow*>(ui)->cbBaudRate->setCurrentIndex(baud);
}

QString CustomSettings::configFile()
{
    QString filePath = __FILE__;
    return filePath.split("/Settings/customsettings.cpp")[0] + "/config.ini";
}

