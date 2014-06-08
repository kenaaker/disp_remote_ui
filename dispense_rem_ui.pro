#-------------------------------------------------
#
# Project created by QtCreator 2014-06-02T09:49:36
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dispense_rem_ui
TEMPLATE = app

SOURCES += main.cpp\
        disp_remote_ui.cpp \
        ssl_client.cpp \
        qt-watch.cpp \
        zconfserviceclient.cpp \
        zconfservicebrowser.cpp

HEADERS  += disp_remote_ui.h \
        ssl_client.h \
        qt-watch.h \
        zconfserviceclient.h \
        zconfservicebrowser.h

LIBS += -lavahi-common -lavahi-client

RESOURCES += disp_rem_ui.qrc

FORMS    += disp_remote_ui.ui

CONFIG += mobility
MOBILITY = 

# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/securesocketclient
INSTALLS += target

