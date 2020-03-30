#ifndef _WIDGETS_MBBUTTON_H
#define _WIDGETS_MBBUTTON_H

// project
#include "data.h"

// Qt headers
#include <QPushButton>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>

// std
#include <memory>


class MbButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(int cmdAddress READ cmdAddress WRITE setAddress NOTIFY cmdAddressChanged)
    Q_PROPERTY(int enableAddress READ enableAddress WRITE setEnableAddress NOTIFY enableAddressChanged)
    Q_PROPERTY(int cmdValue READ cmdValue WRITE setValue NOTIFY cmdValueChanged)

public:
    explicit MbButton(QWidget *parent = nullptr);
    explicit MbButton(const MbButton& button, QWidget *parent = nullptr);
    virtual ~MbButton() {}

    // Properties
    int cmdAddress() const { return m_address; }
    int cmdValue() const { return m_value; }

    void setMbRegisterMap(QSharedPointer<MbData::MbRegisterMap> ptr) { m_ptrMbRegisterMap = ptr; }
    int enableAddress() const { return m_enableAddress; }

 signals:
     // Properties
     void cmdAddressChanged(int cmdAddress);
     void cmdValueChanged(int cmdValue);
     void enableAddressChanged(int enableAddress);

     void dataChanged(int data);

 public slots:
     // Properties
     void setAddress(int cmdAddress);
     void setValue(int cmdValue);
     void setEnableAddress(int enableAddress);

     void onMbDataUpdate();

 protected:
     int m_address;
     int m_value;
     bool m_dataReady;
    QSharedPointer<MbData::MbRegisterMap> m_ptrMbRegisterMap;

 private:
     bool isAddressValid(int addr);
     bool isValueValid(int cmdValue);

     int m_enableAddress;

     // QWidget interface
protected:
     void mousePressEvent(QMouseEvent *event) override;

     // QWidget interface
protected:
     void paintEvent(QPaintEvent *event) override;
};

// To use Q_DECLARE_METATYPE, we need:
// - default constructor;
// - constructor of copy;
// - virtual destructor
Q_DECLARE_METATYPE(MbButton)

#endif
