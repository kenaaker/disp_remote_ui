/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "ssl_client.h"

#include <QSslSocket>

SslClient::SslClient(QWidget *parent)
    : QWidget(parent), socket(0) {
}

SslClient::~SslClient() {
}

void SslClient::secureConnect() {
    if (!socket) {
        socket = new QSslSocket(this);

    }
    /* Add self-signed client and server certificates and CA */
    socket->addCaCertificates(":/sensorweb_ca.pem");
    socket->setLocalCertificate(":/sensorweb_client.pem");
    socket->setPrivateKey(":/sensorweb_client.key", QSsl::Rsa, QSsl::Pem, "var6look");

    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(encrypted()),
            this, SLOT(socketEncrypted()));
    connect(socket, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(sslErrors(QList<QSslError>)));
    connect(socket, SIGNAL(readyRead()),
            this, SLOT(socketReadyRead()));

    QList<QSslCertificate> web_sensor_cert = QSslCertificate::fromPath(":/sensorweb_system_certificate.pem");
    QSslError self_signed_error(QSslError::SelfSignedCertificate, web_sensor_cert.at(0));
    QSslError host_name_mismatch(QSslError::HostNameMismatch, web_sensor_cert.at(0));
    QList<QSslError> expected_ssl_errors;
    expected_ssl_errors.append(self_signed_error);
    expected_ssl_errors.append(host_name_mismatch);
    socket->ignoreSslErrors(expected_ssl_errors);

    socket->connectToHostEncrypted("mars.aaker.org", 45046);
}

void SslClient::socketStateChanged(QAbstractSocket::SocketState state) {
    if (state == QAbstractSocket::UnconnectedState) {
        socket->deleteLater();
        socket = 0;
    }
}

void SslClient::socketEncrypted() {
    if (!socket) {
        return;                 // might have disconnected already
    } else {

    } /* endif */
}

void SslClient::socketReadyRead() {
}

void SslClient::sendData() {
    socket->write("data\r\n");
}

void SslClient::sslErrors(const QList<QSslError> &errors) {
    foreach (const QSslError &error, errors) {
        ;
    } /* endfor */

    socket->ignoreSslErrors();

    // did the socket state change?
    if (socket->state() != QAbstractSocket::ConnectedState) {
        socketStateChanged(socket->state());
    } /* endif */
}