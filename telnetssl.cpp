#include "telnetssl.h"
#include "ui_telnetssl.h"

TelnetSSL::TelnetSSL(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TelnetSSL)
{
    ui->setupUi(this);
}

TelnetSSL::~TelnetSSL()
{
    delete ui;
}
