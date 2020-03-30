#include "message.h"

#include "QVBoxLayout"

Message::Message(QWidget *parent) : MbWidget(parent),
    m_onColor(Qt::gray),
    m_onTextColor(Qt::black),
    m_onText("Message"),

    m_offColor(Qt::gray),
    m_offTextColor(Qt::black),
    m_offText("Message"),

    m_defColor(Qt::gray),
    m_defTextColor(Qt::black),
    m_defText("Message"),

    m_flash(false),
    m_timer(new QTimer(this)),
    m_tick(false)
{
    // Ticks
    m_timer->setInterval(1000);
    m_timer->setSingleShot(false);
    m_timer->start();
    connect(m_timer, &QTimer::timeout, this, &Message::timerTimeout);
    changeTimerState(m_flash);
}


Message::Message(const Message &message, QWidget *parent) : Message(parent)
{
    m_onText = message.m_onText;
    m_onColor = message.m_onColor;
    m_offColor = message.m_offColor;
    m_offText = message.m_offText;
    m_defColor = message.m_defColor;
    m_defText = message.m_defText;
}


Message &Message::operator=(const Message &message)
{
    if (this == &message)
        return *this;

    m_onText = message.m_onText;
    m_onColor = message.m_onColor;
    m_offText = message.m_offText;
    m_offText = message.m_offText;
    m_defColor = message.m_defColor;
    m_defText = message.m_defText;
//    *m_timer = *message.m_timer;
    m_tick = message.m_tick;

    return *this;
}


void Message::onWidgetUpdate()
{
    if (m_varValue.canConvert(QVariant::Bool) && BOOL == m_valueType) {
//        qDebug() << "Widget is updated: addr="
//                 << m_regAddr << "." << m_bitAddr << " : "
//                 << "value=" << m_varValue.toBool();
    }
    else if (m_varValue.canConvert(QVariant::Int) && INT == m_valueType) {
//        qDebug() << "Widget is updated: addr="
//                 << m_regAddr << "." << m_bitAddr << " : "
//                 << "value=" << m_varValue.toInt();
    }
    else {
        qDebug() << "onWidgetUpdate(): unsupported type(" << m_varValue << ", "
                 << static_cast<int>(m_valueType) << ")";
        return;
    }
    update();
}


void Message::paintEvent(QPaintEvent *)
{
        drawRectangle();
//    qDebug() << "Message::paintEvent, m_flash=" << m_flash;

//    QPainter p( this );
//        //    p.fillRect( rect(), QBrush( m_tick? Qt::blue : Qt::darkBlue ) );
//    if (m_flash) {
//        p.fillRect( rect(), QBrush( m_tick? m_onColor : m_offColor) );
//        p.setPen( QPen(m_tick? m_onTextColor : m_offTextColor));
//        p.drawText(20, 20, m_tick ? m_onText : m_offText);
//    }
//    else {
//        drawRectangle();
//    }
}


void Message::timerTimeout()
{
//    qDebug() << "timerTimeout()";
    m_tick = !m_tick;
    if (m_flash) {
        update();
    }
}


/*!
 * \brief Starts/Stops timer
 * \param[in] flash - true-to start, false-to stop
 * \return curren timer state (true - is running)
 */
bool Message::changeTimerState(bool flash) {
    qDebug() << "changeTimerState(" << flash << ")";
    if (flash && !m_timer->isActive())
        m_timer->start();
    else if (!flash && m_timer->isActive()) {
        m_timer->stop();
    }
    return m_timer->isActive();
}


void Message::drawRectangle()
{
    QPainter p(this);

    if (MbData::Quality::Good != m_quality) { // Not good qualiti - default style
        p.fillRect( rect(), QBrush(m_defColor));
        p.setPen( QPen(m_defTextColor));
        p.drawText(20, 20, m_defText);
    }
    else {
        bool value;
        if (m_varValue.canConvert(QVariant::Bool) && BOOL == m_valueType) {
            value = m_varValue.toBool();
        }
        else if (m_varValue.canConvert(QVariant::Int) && INT == m_valueType) {
            value = static_cast<bool>(m_varValue.toInt());
        }
        else {
            qDebug() << "onWidgetUpdate(): unsupported type(" << m_varValue << ", "
                     << static_cast<int>(m_valueType) << ")";
            return;
        }

        if (m_flash) {
            p.fillRect( rect(), QBrush( m_tick && value ? m_onColor : m_offColor) );
            p.setPen( QPen(m_tick && value ? m_onTextColor : m_offTextColor));
            p.drawText(20, 20, m_tick && value ? m_onText : m_offText);
        }
        else {
//            QLinearGradient gradient(0, 0, 0, height());
//            gradient.setColorAt(0, Qt::red);
//            gradient.setColorAt(0.35, Qt::white);
//            gradient.setColorAt(1, Qt::red);
//            p.fillRect(rect(), gradient);
            p.fillRect( rect(), QBrush( value? m_onColor : m_offColor) );

//            QColor white1(255,255,255,200);
//            QColor white0(255,255,255,100);
//            QLinearGradient shine(0, 0, 0, height());
//            shine.setColorAt(0.0,white1);
//            shine.setColorAt(1.0,white0);
//            p.setBrush(shine);
//            p.drawEllipse(-10, -10, width()-10, height()-10);

            p.setPen( QPen(value? m_onTextColor : m_offTextColor));
            p.drawText(20, 20, value ? m_onText : m_offText);
        }
    }
}


void Message::drawMessage()
{

}

