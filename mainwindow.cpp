#include "mainwindow.h"
#include "qglobal.h"
#include "ui_mainwindow.h"

#include "QSettings"
#include "QFile"
#include "QJsonDocument"
#include "QJsonObject"

#define ORG_NAME "VolAnd"
#define APP_NAME "UserVerificator"
#define GROUP_NAME "MainWindowSettings"
#define UI_FILENAME "ui.json"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (!this->readSettings()) {
        qWarning("Во время загрузки параметров формы произошла ошибка.");
    }
}

MainWindow::~MainWindow()
{
    if (!writeSettings()) {
        qWarning("Во время записи параметров формы произошла ошибка.");
    }

    delete ui;
}


bool MainWindow::writeSettings() {
    return this->writeJSONSettings();
    //this->writeQSettings();
}

bool MainWindow::readSettings() {
    return this->readJSONSettings();
    //this->readQSettings();
}

bool MainWindow::writeQSettings()
{
    QSettings settings(ORG_NAME, APP_NAME);

    settings.beginGroup(GROUP_NAME);

    settings.setValue("username_tv",        ui->username_tv->text());

    settings.setValue("phone_aid",          ui->phone_aid->text());
    settings.setValue("phone_model_cb",     ui->phone_model_cb->currentIndex());
    settings.setValue("phone_os_cb",        ui->phone_os_cb->currentIndex());

    settings.setValue("cl_country_cb",      ui->cl_country_cb->currentIndex());
    settings.setValue("cl_state_cb",        ui->cl_state_cb->currentIndex());

    settings.setValue("user_lat",           ui->user_lat->text());
    settings.setValue("user_lon",           ui->user_lon->text());
    settings.setValue("user_alt",           ui->user_alt->text());

    settings.setValue("proxy_ipaddr",       ui->proxy_ipaddr->text());
    settings.setValue("proxy_port",         ui->proxy_port->text());
    settings.setValue("proxy_user",         ui->proxy_user->text());
    settings.setValue("proxy_pass",         ui->proxy_pass->text());
    settings.setValue("proxy_change_ip",    ui->proxy_change_ip->text());

    settings.setValue("local_server",       ui->local_server->text());
    settings.setValue("local_port",         ui->local_port->text());
    settings.setValue("browser",            ui->browser->currentIndex());

    settings.endGroup();

    return true;
}

bool MainWindow::readQSettings()
{
    QSettings settings(ORG_NAME, APP_NAME);
    settings.beginGroup(GROUP_NAME);

    ui->username_tv->setText(settings.value("username_tv", "").toString());

    ui->phone_aid->setText(settings.value("phone_aid", "").toString());
    ui->phone_model_cb->setCurrentIndex(settings.value("phone_model_cb", -1).toInt());
    ui->phone_os_cb->setCurrentIndex(settings.value("phone_os_cb", -1).toInt());

    ui->cl_country_cb->setCurrentIndex(settings.value("cl_country_cb", -1).toInt());
    ui->cl_state_cb->setCurrentIndex(settings.value("cl_state_cb", -1).toInt());

    ui->user_lat->setText(settings.value("user_lat", "").toString());
    ui->user_lon->setText(settings.value("user_lon", "").toString());
    ui->user_alt->setText(settings.value("user_alt", "").toString());

    ui->proxy_ipaddr->setText(settings.value("proxy_ipaddr", "").toString());
    ui->proxy_port->setText(settings.value("proxy_port", "").toString());
    ui->proxy_user->setText(settings.value("proxy_user", "").toString());
    ui->proxy_pass->setText(settings.value("proxy_pass", "").toString());
    ui->proxy_change_ip->setText(settings.value("proxy_change_ip", "").toString());

    ui->local_server->setText(settings.value("local_server", "").toString());
    ui->local_port->setText(settings.value("local_port", "").toString());
    ui->browser->setCurrentIndex(settings.value("browser", -1).toInt());

    settings.endGroup();

    return true;
}

bool MainWindow::writeJSONSettings()
{
    QFile saveFile(UI_FILENAME);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Ошибка при открытии файла: %s", UI_FILENAME);
        return false;
    }

//    QJsonDocument jsonDoc;
    QJsonObject json;

    QList<QLineEdit *> qEdits = this->findChildren<QLineEdit *>();

    foreach(auto child, qEdits) {
        QString child_name(child->objectName());
        json.insert(child_name, child->text());
    }

    QList<QComboBox *> qCombos = this->findChildren<QComboBox *>();

    foreach(auto child, qCombos) {
        QString child_name(child->objectName());
        json.insert(child_name, child->currentIndex());
    }

    saveFile.write(QJsonDocument(json).toJson());

    return true;
}

bool MainWindow::readJSONSettings()
{
    QFile loadFile(UI_FILENAME);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Ошибка при открытии файла: %s", UI_FILENAME);
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();

    QList<QLineEdit *> qEdits = this->findChildren<QLineEdit *>();

    foreach(auto child, qEdits) {
        QString child_name(child->objectName());
        if (json.contains(child_name) && json[child_name].isString()) {
            child->setText(json[child_name].toString());
        }
        else {
            qWarning("Проверьте наличие параметра %s и его тип в конфигурационном файле.", child_name.toStdString().c_str());
            //return false;
        }
    }

    QList<QComboBox *> qCombos = this->findChildren<QComboBox *>();

    foreach(auto child, qCombos) {
        QString child_name(child->objectName());
        if (json.contains(child_name) && json[child_name].isDouble()) {
            child->setCurrentIndex(json[child_name].toInt());
        }
        else {
            qWarning("Проверьте наличие параметра %s и его тип в конфигурационном файле.", child_name.toStdString().c_str());
            //return false;
        }
    }

    return true;
}
