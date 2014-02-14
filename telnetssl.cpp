#include <QMessageBox>

#include "telnetssl.h"
#include "ui_telnetssl.h"

TelnetSSL::TelnetSSL(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TelnetSSL)
{
    ui->setupUi(this);

    QObject::connect(ui->actionInfo, SIGNAL(triggered()),
            this, SLOT(printInfo()));
}

void TelnetSSL::printInfo()
{
    QMessageBox msgBox;
    msgBox.setText("TelnetSSL Version 0.0.1");
    msgBox.setWindowTitle("TelnetSSL Info");
    msgBox.exec();
}

TelnetSSL::~TelnetSSL()
{
    delete ui;
}
