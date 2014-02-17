#include <dialogsslerrors.h>
#include <qdialog.h>
#include <qglobal.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qsslcipher.h>
#include <qsslsocket.h>
#include <sslcomm.h>
#include <ui_sslcomm.h>

SslComm::SslComm(QWidget *parent) :
        QWidget(parent), ui(new Ui::SslComm), labelStatus(0), socket(
                new QSslSocket(this))
{
    ui->setupUi(this);

    ui->host->setFocus();

    connect(ui->buttonConnect, SIGNAL(clicked()), this,
            SLOT(changeConnectionState()));

    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,
            SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(encrypted()), this, SLOT(socketEncrypted()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(socketError(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(sslErrors(QList<QSslError>)), this,
            SLOT(sslErrors(QList<QSslError>)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
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
    if (socket->state() == QAbstractSocket::UnconnectedState)
    {
        socket->connectToHostEncrypted(ui->host->text(), ui->port->value());
    }
    else
    {
        socket->disconnectFromHost();
    }
}

void SslComm::socketStateChanged(QAbstractSocket::SocketState state)
{
    switch (state)
    {
        case QAbstractSocket::UnconnectedState:
            setStatus("Unconnected.");
            ui->buttonConnect->setText("&Connect");
            break;
        case QAbstractSocket::ConnectingState:
            setStatus("Connecting ...");
            break;
        case QAbstractSocket::ConnectedState:
            setStatus("Connected.");
            ui->buttonConnect->setText("&Disconnect");
            break;
        default:
            break;
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

void SslComm::socketError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
        case QAbstractSocket::HostNotFoundError:
            setStatus("Host not found.");
            break;
        default:
            break;
    }
}

void SslComm::sslErrors(QList<QSslError> errors)
{
    if (errors.length() == 0)
    {
        return;
    }

    DialogSslErrors errorDialog(this);
    foreach(const QSslError& error, errors){
    errorDialog.addError(error.errorString());
}
    if (errorDialog.exec() == QDialog::Accepted)
    {
        socket->ignoreSslErrors(errors);
    }
    else
    {
        socket->disconnectFromHost();
    }

    if (socket->state() != QAbstractSocket::ConnectedState)
    {
        socketStateChanged(socket->state());
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
