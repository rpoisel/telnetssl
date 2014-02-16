#include <QMessageBox>

#include "sslcomm.h"
#include "ui_sslcomm.h"

SslComm::SslComm(QWidget *parent) :
        QWidget(parent), ui(new Ui::SslComm), socket(0)
{
    ui->setupUi(this);

    ui->host->setFocus();

    connect(ui->connect, SIGNAL(clicked()), this, SLOT(changeConnectionState()));
}

SslComm::~SslComm()
{
    delete ui;
}

void SslComm::changeConnectionState()
{
    if (!socket)
    {
        // TODO create SSL socket
        socket = new QSslSocket(this);
        // TODO establish connection

        // update UI
        ui->connect->setText("&Disconnect");
    }
    else
    {
        // TODO tear down SSL connection

        // TODO remove SSL socket
        delete socket;
        socket = 0;

        // update UI
        ui->connect->setText("&Connect");
    }
}
