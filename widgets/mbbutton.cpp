//#include "../Widgets/mbbutton.h"
#include "mbbutton.h"

MbButton::MbButton(QWidget *parent) :
    QPushButton(parent)
{
        QString style = "QPushButton::hover {background-color: blue}";
        style += "QPushButton {background-color: yellow}";
        style += "QPushButton::disabled {background-color: blue}";
        style += "QPushButton::enabled {background-color: gray}";
        style += "QPushButton::pressed {background-color: white}";
        this->setStyleSheet(style);
}

MbButton::MbButton(const MbButton &button, QWidget *parent) :  QPushButton(parent),
    m_address(button.m_address),
    m_value(button.m_value),
    m_ptrMbRegisterMap(button.m_ptrMbRegisterMap)
{
        QString style = "QPushButton::hover {background-color: blue}";
        style += "QPushButton {background-color: yellow}";
        style += "QPushButton::disabled {background-color: white}";
        style += "QPushButton::enabled {background-color: gray}";
        style += "QPushButton::pressed {background-color: blue}";
        this->setStyleSheet(style);
}


void MbButton::setAddress(int address)
{
    if (m_address == address)
        return;

    if (!isAddressValid(address))
        return;

    m_address = address;
    emit cmdAddressChanged(m_address);
}


void MbButton::setValue(int value)
{
    if (m_value == value)
        return;

    if (!isValueValid(value))
        return;

    m_value = value;
    emit cmdValueChanged(m_value);
}


void MbButton::onMbDataUpdate()
{
    if (nullptr == m_ptrMbRegisterMap) {
        qDebug() << "DigitInidicator: MbRegisterMap ins't defined";
        return;
    }

//    Q_ASSERT(wRegAddr <= m_ptrMbRegisterMap->size());

//    quint16 regValue = m_ptrMbRegisterMap->at(wRegAddr).value;
//    MbData::Quality quality = m_ptrMbRegisterMap->at(wRegAddr).qulity;
//    if (m_value != regValue || m_quality != quality) {
//        qDebug() << "DigitIndicatorUpdate: " << m_ptrAddr->address() << ", value=" <<  regValue;
//        m_value = regValue;
//        m_quality = quality;
//        update();
//    }
}


void MbButton::setEnableAddress(int enableAddress)
{
    if (m_enableAddress == enableAddress)
        return;

    m_enableAddress = enableAddress;
    emit enableAddressChanged(m_enableAddress);
}


/*!
 * \brief Check is address between 0..65565
 * \param[in] addr - checked address;
 * \return true - successfully
 */
bool MbButton::isAddressValid(int addr)
{
    return 0 <= addr && addr <= 65565;
}


/*!
 * \brief Check is value between 0..65565
 * \param[in] value - checked value;
 * \return true - successfully
 */
bool MbButton::isValueValid(int value)
{
    return 0 <= value && value <= 65565;
}


void MbButton::mousePressEvent(QMouseEvent *event)
{
    QAbstractButton::mousePressEvent(event);
//    qDebug() << "mousePressEvent: " << m_value;

    if (nullptr == m_ptrMbRegisterMap) {
        qDebug() << "MbWidget: MbRegisterMap ins't defined";
        return;
    }

    Q_ASSERT(m_address <= m_ptrMbRegisterMap->size());
    emit cmdValueChanged(m_value);


//    m_quality = m_ptrMbRegisterMap->at(m_regAddr).qulity;
//    m_value = m_ptrMbRegisterMap->at(m_regAddr).value;
//    m_time = m_ptrMbRegisterMap->at(m_regAddr).time;
}


void MbButton::paintEvent(QPaintEvent *event)
{
//        QString style = "QPushButton::hover {background-color: blue}";
////        QString style;
//        style += "QPushButton {background-color: yellow}";
//        style += "QPushButton::disabled {background-color: white}";
//        style += "QPushButton::enabled {background-color: gray}";
//        style += "QPushButton::pressed {background-color: blue}";
//        this->setStyleSheet(style);
        QPushButton::paintEvent(event);
}
