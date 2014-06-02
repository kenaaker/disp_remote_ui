#ifndef DISP_REMOTE_UI_H
#define DISP_REMOTE_UI_H

#include <QMainWindow>

namespace Ui {
class disp_remote_ui;
}

class disp_remote_ui : public QMainWindow
{
    Q_OBJECT

public:
    explicit disp_remote_ui(QWidget *parent = 0);
    ~disp_remote_ui();

private:
    Ui::disp_remote_ui *ui;
};

#endif // DISP_REMOTE_UI_H
