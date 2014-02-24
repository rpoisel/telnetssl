#include <dialogsslerrors.h>
#include <qcheckbox.h>
#include <qdialog.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qscrollbar.h>
#include <qspinbox.h>
#include <qsslcipher.h>
#include <qsslsocket.h>
#include <qtextcursor.h>
#include <qtextedit.h>
#include <sslcomm.h>
#include <ui_sslcomm.h>

SslComm::SslComm(QWidget *parent) :
        QWidget(parent), ui(new Ui::SslComm), labelStatus(0), socket(
                new QSslSocket(this))
{
    ui->setupUi(this);

    ui->host->setFocus();

    /* QT ui connections */
    connect(ui->buttonConnect, SIGNAL(clicked()), this,
            SLOT(changeConnectionState()));
    connect(ui->input, SIGNAL(returnPressed()), this, SLOT(sendData()));

    /* socket connections */
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,
            SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(socketError(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
    connect(socket, SIGNAL(sslErrors(QList<QSslError>)), this,
            SLOT(sslErrors(QList<QSslError>)));
    connect(socket, SIGNAL(encrypted()), this, SLOT(socketEncrypted()));

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
        if (ui->ssl->isChecked())
        {
            socket->connectToHostEncrypted(ui->host->text(), ui->port->value());
        }
        else
        {
            socket->connectToHost(ui->host->text(), ui->port->value());
        }
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
            ui->input->setEnabled(false);
            ui->buttonConnect->setText("&Connect");
            break;
        case QAbstractSocket::ConnectingState:
            setStatus("Connecting ...");
            break;
        case QAbstractSocket::ConnectedState:
            setStatus("Connected.");
            ui->buttonConnect->setText("&Disconnect");
            ui->input->setEnabled(true);
            ui->input->setFocus();
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
        case QAbstractSocket::SslHandshakeFailedError:
            setStatus("SSL handshake failed.");
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
    QList<QSslError>::ConstIterator it = errors.constBegin();
    for (; it != errors.constEnd(); ++it)
    {
        errorDialog.addError((*it).errorString());
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
    QString result = QString::fromUtf8(socket->readAll());
    QTextCursor cursor = ui->output->textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(result);
    ui->output->verticalScrollBar()->setValue(
            ui->output->verticalScrollBar()->maximum());
}

void SslComm::sendData()
{
    if (!socket)
    {
        return;
    }
    socket->write(ui->input->text().toUtf8());
    socket->write("\n");
    ui->input->setText("");
}

void SslComm::setStatus(QString status)
{
    if (labelStatus)
    {
        labelStatus->setText(status);
    }
}
