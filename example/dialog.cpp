#include "dialog.h"
#include "ui_dialog.h"

#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

//    qRegisterMetaType<Data>("Data");
//    connect(ui->btLed1, &MyButton::buttonStateChanged, ui->boolIndicator1, &Indicator::onIndicatorUpdate);
//    connect(ui->btLed2, &MyButton::buttonStateChanged, ui->boolIndicator2, &Indicator::onIndicatorUpdate);
//    connect(ui->btLed3, &MyButton::buttonStateChanged, ui->boolIndicator3, &Indicator::onIndicatorUpdate);
//    connect(ui->btLed4, &MyButton::buttonStateChanged, ui->boolIndicator4, &Indicator::onIndicatorUpdate);

    m_oiserver.setClientAddress("192.168.1.46:10502");

    // Add all Indicator widgets from ui form
    qDebug() << "Dialog: It has been found following widgets on UI:";
    QList<MbWidget*> widgets = this->findChildren<MbWidget*>();
    m_oiserver.addMbWidgets(widgets);
    QList<MbButton*> buttons = this->findChildren<MbButton*>();
    m_oiserver.addMbButtons(buttons);

    m_oiserver.start();
}

Dialog::~Dialog()
{
    delete ui;
}
