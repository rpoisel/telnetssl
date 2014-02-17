#include <qglobal.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qsslcipher.h>
#include <qsslsocket.h>
#include <sslcomm.h>
#include <dialogsslerrors.h>
#include <ui_sslcomm.h>
/* #include <ui_dialogsslerrors.h> */

SslComm::SslComm(QWidget *parent) :
        QWidget(parent), ui(new Ui::SslComm), labelStatus(0), socket(0)
{
    ui->setupUi(this);

    ui->host->setFocus();

    connect(ui->buttonConnect, SIGNAL(clicked()), this,
            SLOT(changeConnectionState()));
}

SslComm::~SslComm()
{
    delete ui;
    if (socket)
    {
        delete socket;
    }
}

void SslComm::setLabelStatus(QLabel* labelStatus)
{
    this->labelStatus = labelStatus;
}

void SslComm::changeConnectionState()
{
    if (!socket)
    {
        socket = new QSslSocket(this);

        connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
        connect(socket, SIGNAL(encrypted()), this, SLOT(socketEncrypted()));
        connect(socket, SIGNAL(sslErrors(QList<QSslError>)), this,
                SLOT(sslErrors(QList<QSslError>)));
        connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));

        socket->connectToHostEncrypted(ui->host->text(), ui->port->value());

        // update UI
        ui->buttonConnect->setText("&Disconnect");
    }
    else
    {
        // TODO tear down SSL connection

        // TODO remove SSL socket
        delete socket;
        socket = 0;

        // update UI
        ui->buttonConnect->setText("&Connect");
    }
}

void SslComm::socketStateChanged(QAbstractSocket::SocketState state)
{
    if (QAbstractSocket::UnconnectedState == state)
    {
        setStatus("Unconnected.");
    }
    else if (QAbstractSocket::ConnectingState == state)
    {
        setStatus("Connecting ...");
    }
    else if (QAbstractSocket::ConnectedState == state)
    {
        setStatus("Connected.");
    }
}

void SslComm::socketEncrypted()
{
    if (!socket)
    {
        return;
    }

    QSslCipher ciph = socket->sessionCipher();
    QString cipher =
            QString("%1, %2 (%3/%4)").arg(ciph.authenticationMethod()).arg(
                    ciph.name()).arg(ciph.usedBits()).arg(ciph.supportedBits());
}

void SslComm::sslErrors(QList<QSslError> errors)
{
    if (errors.length() == 0)
    {
        return;
    }

    DialogSslErrors errorDialog(this);
    foreach(const QSslError& error, errors)
    {
        // add error messages to list
    }
    if (errorDialog.exec() == QDialog::Accepted)
    {
            socket->ignoreSslErrors(errors);
    }
}

void SslComm::socketReadyRead()
{

}

void SslComm::setStatus(QString status)
{
    if (labelStatus)
    {
        labelStatus->setText(status);
    }
}
