#include <qaction.h>
#include <qlabel.h>
#include <qmessagebox.h>
#include <qobjectdefs.h>
#include <qstatusbar.h>
#include <qtelnetssl.h>
#include <ui_telnetssl.h>

QTelnetSSL::QTelnetSSL(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::TelnetSSL)
{
    ui->setupUi(this);

    mainForm = new SslComm(this);

    this->setCentralWidget(mainForm);

    QLabel* statusLabel = new QLabel;
    statusBar()->addWidget(statusLabel, 1);
    mainForm->setStatus(statusLabel);

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
