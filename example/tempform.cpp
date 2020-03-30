#include "tempform.h"
#include "ui_tempform.h"

TempForm::TempForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TempForm)
{
    ui->setupUi(this);
}

TempForm::~TempForm()
{
    delete ui;
}
