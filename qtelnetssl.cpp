#include <QMessageBox>

#include "qtelnetssl.h"
#include "ui_telnetssl.h"

QTelnetSSL::QTelnetSSL(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::TelnetSSL)
{
    ui->setupUi(this);

    mainForm = new SslComm;

    this->setCentralWidget(mainForm);

    connect(ui->actionInfo, SIGNAL(triggered()), this,
            SLOT(printInfo()));
}

void QTelnetSSL::printInfo()
{
    QMessageBox msgBox;
    msgBox.setText("TelnetSSL Version 0.0.1");
    msgBox.setWindowTitle("TelnetSSL Info");
    msgBox.exec();
}

QTelnetSSL::~QTelnetSSL()
{
    delete ui;
    delete mainForm;
}
