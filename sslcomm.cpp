#include "sslcomm.h"
#include "ui_sslcomm.h"

SslComm::SslComm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SslComm),
    socket(0)
{
    ui->setupUi(this);

    ui->host->setFocus();
}

SslComm::~SslComm()
{
    delete ui;
}
