#include <dialogsslerrors.h>
#include <qcolor.h>
#include <qlistwidget.h>
#include <qstring.h>
#include <ui_dialogsslerrors.h>

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


void DialogSslErrors::addError(QString errorMessage)
{
    QListWidgetItem* item = new QListWidgetItem(errorMessage);
    item->setForeground(QColor::fromRgb(255, 0, 0));
    ui->listWidget->addItem(item);
}
