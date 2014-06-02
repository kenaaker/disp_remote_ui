#include "disp_remote_ui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    disp_remote_ui w;
    w.show();

    return a.exec();
}
