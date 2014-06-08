#include "disp_remote_ui.h"
#include "ui_disp_remote_ui.h"

disp_remote_ui::disp_remote_ui(QWidget *parent) : QMainWindow(parent),
                                    ui(new Ui::disp_remote_ui) {
    ui->setupUi(this);
    disp_connection.secureConnect();
    connect(&disp_connection, SIGNAL(socket_up()), this, SLOT(socket_up()));
    connect(&disp_connection, SIGNAL(socket_down()), this, SLOT(socket_down()));
    disp_svc = new ZConfServiceBrowser(this);
    disp_svc->browse("_dispensaryui._tcp");
    connect(disp_svc, SIGNAL(serviceEntryAdded(QString)), this, SLOT(service_found(QString)));
}

disp_remote_ui::~disp_remote_ui() {
    delete ui;
    delete disp_svc;
}

void disp_remote_ui::service_found(QString service_string) {
    ZConfServiceEntry this_service;
    qDebug() << "Found dispensary at " << service_string;
    this_service = disp_svc->serviceEntry(service_string);
    qDebug() << "Service entry is " << this_service.ip << "protocol is " << this_service.protocolName() << "host" << this_service.host << "port is" << this_service.port;
}

void disp_remote_ui::socket_up() {
    ui->dispensary_controls->setEnabled(true);
}

void disp_remote_ui::socket_down() {
    ui->dispensary_controls->setEnabled(false);
}

void disp_remote_ui::on_pushButton_clicked() {
    qApp->quit();
}

void disp_remote_ui::on_counter_clockwise_1_clicked() {
    QString cmd("counter_clockwise_1");
    disp_connection.sendData(cmd);
}

void disp_remote_ui::on_home_button_clicked() {
    QString cmd("home");
    disp_connection.sendData(cmd);
}

void disp_remote_ui::on_clockwise_1_clicked() {
    QString cmd("clockwise_1");
    disp_connection.sendData(cmd);
}

void disp_remote_ui::on_dispense_position_clicked() {
    QString cmd("dispense");
    disp_connection.sendData(cmd);
}
