#include "dialogsslerrors.h"
#include "ui_dialogsslerrors.h"

DialogSslErrors::DialogSslErrors(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSslErrors)
{
    ui->setupUi(this);
}

DialogSslErrors::~DialogSslErrors()
{
    delete ui;
}
