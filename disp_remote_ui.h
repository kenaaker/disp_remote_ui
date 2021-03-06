#ifndef DISP_REMOTE_UI_H
#define DISP_REMOTE_UI_H

#include <QMainWindow>
#include <QApplication>
#include <ssl_client.h>
#include "zconfservicebrowser.h"

namespace Ui {
class disp_remote_ui;
}

class disp_remote_ui : public QMainWindow
{
    Q_OBJECT

public:
    explicit disp_remote_ui(QWidget *parent = 0);
    ~disp_remote_ui();
public slots:
    void socket_up();
    void socket_down();
    void service_found(QString);

private slots:
    void on_pushButton_clicked();

    void on_counter_clockwise_1_clicked();

    void on_home_button_clicked();

    void on_clockwise_1_clicked();

    void on_dispense_position_clicked();

private:
    Ui::disp_remote_ui *ui;
    SslClient disp_connection;
    ZConfServiceBrowser *disp_svc;
};

#endif // DISP_REMOTE_UI_H
