#ifndef DIALOG_H
#define DIALOG_H

#include <oiserver.h>

#include <QDialog>
#include <QTimer>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    OIServer m_oiserver;

};

#endif // DIALOG_H
