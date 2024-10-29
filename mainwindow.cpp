#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QSettings"

#define ORG_NAME "VolAnd"
#define APP_NAME "UserVerificator"
#define GROUP_NAME "MainWindowSettings"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->readSettings();
}

MainWindow::~MainWindow()
{
    writeSettings();
    delete ui;
}




/*void MainWindow::on_username_tv_textEdited(const QString &arg1)
{
    //
}
*/

void MainWindow::writeSettings()
{
    QSettings settings(ORG_NAME, APP_NAME);
    // Сохранить в INI-файле
    //settings.setDefaultFormat(QSettings::IniFormat);
    //settings.setPath(QSettings::IniFormat, QSettings::UserScope, ".");

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
}

void MainWindow::readSettings()
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
}
