#include "disp_remote_ui.h"
#include "ui_disp_remote_ui.h"

disp_remote_ui::disp_remote_ui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::disp_remote_ui)
{
    ui->setupUi(this);
}

disp_remote_ui::~disp_remote_ui()
{
    delete ui;
}
