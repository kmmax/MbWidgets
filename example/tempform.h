#ifndef TEMPFORM_H
#define TEMPFORM_H

#include <QWidget>

namespace Ui {
class TempForm;
}

class TempForm : public QWidget
{
    Q_OBJECT

public:
    explicit TempForm(QWidget *parent = 0);
    ~TempForm();

private:
    Ui::TempForm *ui;
};

#endif // TEMPFORM_H
