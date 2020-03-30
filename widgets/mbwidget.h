#ifndef _WIDGETS_MBWIDGET_H
#define _WIDGETS_MBWIDGET_H

// project
#include "data.h"

// Qt headers
#include <QWidget>
#include <QVariant>
#include <QDebug>
#include <QSharedPointer>
#include <QtGlobal>
#include <QPainter>

// std
#include <memory.h>

using namespace std;

class MbWidget : public QWidget
{
    Q_OBJECT
    Q_ENUMS(ValueType)
    Q_PROPERTY(ValueType valueType READ valeType WRITE setValueType NOTIFY valueTypeChanged)
    Q_PROPERTY(int regAddr READ regAddr WRITE setRegAddr NOTIFY regAddrChanged)
    Q_PROPERTY(int bitAddr READ bitAddr WRITE setBitAddr NOTIFY bitAddrChanged)
    Q_PROPERTY(int cmdAddr READ cmdAddr WRITE setCmdAddr NOTIFY cmdAddrChanged)
    Q_PROPERTY(int cmdCode READ cmdCode WRITE setCmdCode NOTIFY cmdCodeChanged)

public:
    enum ValueType {
        BOOL,
        REAL,
        INT,
        UINT
    };

    MbWidget(QWidget *parent = nullptr);
    virtual ~MbWidget() override;

    ValueType valeType() const { return m_valueType; }
    int regAddr() const { return m_regAddr; }
    int bitAddr() const { return m_bitAddr; }
    int cmdAddr() const { return m_cmdAddr; }
    int cmdCode() const { return m_cmdCode; }

    void setMbRegisterMap(QSharedPointer<MbData::MbRegisterMap> ptr) { m_ptrMbRegisterMap = ptr; }

public slots:
    void setValueType(ValueType valueType);
    void setRegAddr(int regAddr);
    void setBitAddr(int bitAddr);
    void setCmdAddr(int cmdAddr);
    void setCmdCode(int cmdCode);

    virtual void onDataUpdated();

signals:
    void valueTypeChanged(ValueType valueType);
    void regAddrChanged(int regAddr);
    void bitAddrChanged(int bitAddr);
    void cmdAddrChanged(int cmdAddr);
    void cmdCodeChanged(int cmdCode);

    void cmdActivated();

protected:
    ValueType m_valueType;
    int m_regAddr;
    int m_bitAddr;
    int m_cmdAddr;
    int m_cmdCode;

    QVariant m_varValue;
    MbData::Quality m_quality;
    QTime m_time;

    QSharedPointer<MbData::MbRegisterMap> m_ptrMbRegisterMap;

    virtual void onWidgetUpdate() = 0;

private:
     bool isAddressValid(int addr);
     bool isValueValid(int cmdValue);
};


#endif
