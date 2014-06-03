#include <QApplication>
#include <QMessageBox>
#include "disp_remote_ui.h"

int main(int argc, char *argv[]) {

    Q_INIT_RESOURCE(disp_rem_ui);

    QApplication a(argc, argv);

    if (!QSslSocket::supportsSsl()) {
        QMessageBox::information(0, "Secure Socket Client",
                                 "This system does not support OpenSSL.");
        return -1;
    } else {
        disp_remote_ui w;
        w.show();

        return a.exec();
    } /* endif */
}
