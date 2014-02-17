#ifndef DIALOGSSLERRORS_H
#define DIALOGSSLERRORS_H

#include <QDialog>

namespace Ui {
class DialogSslErrors;
}

class DialogSslErrors : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSslErrors(QWidget *parent = 0);
    ~DialogSslErrors();

private:
    Ui::DialogSslErrors *ui;
};

#endif // DIALOGSSLERRORS_H
