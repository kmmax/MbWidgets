#include "mbwidget.h"
#include "converter.h"


MbWidget::MbWidget(QWidget *parent) :
    QWidget(parent),
    m_valueType(INT),
    m_regAddr(0),
    m_bitAddr(0),
    m_cmdAddr(0),
    m_cmdCode(0)
{
}

MbWidget::~MbWidget()
{

}


void MbWidget::setRegAddr(int regAddr)
{
    if (m_regAddr == regAddr)
        return;

    if (!isAddressValid(regAddr))
        return;

    m_regAddr = regAddr;
    emit regAddrChanged(m_regAddr);
}


void MbWidget::setBitAddr(int bitAddr)
{
    if (m_bitAddr == bitAddr)
        return;

    // Checking for number bit in register
    if (bitAddr < 0 || bitAddr > 15)
        return;

    m_bitAddr = bitAddr;
    emit bitAddrChanged(m_bitAddr);
}


void MbWidget::setCmdAddr(int cmdAddr)
{
    if (m_cmdAddr == cmdAddr)
        return;

    if (!isAddressValid(cmdAddr))
        return;

    m_cmdAddr = cmdAddr;
    emit cmdAddrChanged(m_cmdAddr);
}


void MbWidget::setCmdCode(int cmdCode)
{
    if (m_cmdCode == cmdCode)
        return;

    m_cmdCode = cmdCode;
    emit cmdCodeChanged(m_cmdCode);
}


void MbWidget::setValueType(MbWidget::ValueType valueType)
{
    if (m_valueType == valueType)
        return;

    m_valueType = valueType;
    emit valueTypeChanged(m_valueType);
}


void MbWidget::onDataUpdated()
{
//    qDebug() << "MbWidget::onMbDataUpdate()";
    if (nullptr == m_ptrMbRegisterMap) {
        qDebug() << "MbWidget: MbRegisterMap ins't defined";
        return;
    }

    Q_ASSERT(m_regAddr <= m_ptrMbRegisterMap->size());

    m_quality = m_ptrMbRegisterMap->at(m_regAddr).qulity;
    quint16 value16 = m_ptrMbRegisterMap->at(m_regAddr).value;
    quint16 v0 = m_ptrMbRegisterMap->at(m_regAddr).value;
    quint16 v1 = m_ptrMbRegisterMap->at(m_regAddr+1).value;
    float floatValue = Converter::toFloat(v0, v1);
    m_time = m_ptrMbRegisterMap->at(m_regAddr).time;
//    quint16 regValue = 0;
    switch (m_valueType) {
    case BOOL: {
        quint16 regValue = static_cast<quint16>(value16);
        bool bitValue = static_cast<bool>(regValue>>m_bitAddr & 0x0001);
        m_varValue = QVariant::fromValue(static_cast<bool>(bitValue));
        break;
    }
    case INT:
        m_varValue = QVariant::fromValue(static_cast<qint16>(value16));
        break;
    case UINT:
        m_varValue = QVariant::fromValue(static_cast<quint16>(value16));
        break;
    case REAL:
        m_varValue = QVariant::fromValue(static_cast<float>(floatValue));
        break;
    default:
        m_varValue = QVariant();
        break;
    }

    onWidgetUpdate();
}


/*!
 * \brief Check is address between 0..65565
 * \param[in] addr - checked address;
 * \return true - successfully
 */
bool MbWidget::isAddressValid(int addr)
{
    return 0 <= addr && addr <= 65565;
}


/*!
 * \brief Check is value between 0..65565
 * \param[in] value - checked value;
 * \return true - successfully
 */
bool MbWidget::isValueValid(int cmdValue)
{
    return 0 <= cmdValue && cmdValue <= 65565;
}



