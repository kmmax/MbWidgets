#include "indicator.h"
#include "converter.h"

#include "QVBoxLayout"

Indicator::Indicator(QWidget *parent) : MbWidget(parent),
    m_onColor(Qt::gray),
    m_onTextColor(Qt::black),
    m_onText("Indicator"),

    m_defColor(Qt::gray),
    m_defTextColor(Qt::black),
    m_defText("Indicator"),

    m_flash(false),
    m_timer(new QTimer(this)),
    m_tick(false)
{
    // Ticks
    m_timer->setInterval(1000);
    m_timer->setSingleShot(false);
    m_timer->start();
    connect(m_timer, &QTimer::timeout, this, &Indicator::timerTimeout);
    changeTimerState(m_flash);
}


Indicator::Indicator(const Indicator &indicator, QWidget *parent) : Indicator(parent)
{
    m_onText = indicator.m_onText;
    m_onColor = indicator.m_onColor;
    m_defColor = indicator.m_defColor;
    m_defText = indicator.m_defText;
}


Indicator &Indicator::operator=(const Indicator &indicator)
{
    if (this == &indicator)
        return *this;

    m_onText = indicator.m_onText;
    m_onColor = indicator.m_onColor;
    m_defColor = indicator.m_defColor;
    m_defText = indicator.m_defText;
    m_tick = indicator.m_tick;

    return *this;
}


void Indicator::setFormat(Indicator::Format format)
{
    if (m_format == format)
        return;

    m_format = format;
    emit formatChanged(m_format);
    update();
}


void Indicator::onWidgetUpdate()
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
    else if (REAL == m_valueType) {
        ;
    }

    else {
        qDebug() << "onWidgetUpdate(): unsupported type(" << m_varValue << ", "
                 << static_cast<int>(m_valueType) << ")";
        return;
    }
    update();
}


void Indicator::paintEvent(QPaintEvent *)
{
        drawRectangle();
}


void Indicator::timerTimeout()
{
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
bool Indicator::changeTimerState(bool flash) {
    qDebug() << "changeTimerState(" << flash << ")";
    if (flash && !m_timer->isActive())
        m_timer->start();
    else if (!flash && m_timer->isActive()) {
        m_timer->stop();
    }
    return m_timer->isActive();
}


void Indicator::drawRectangle()
{
    QPainter p(this);

    if (MbData::Quality::Good != m_quality) { // Not good qualiti - default style
        p.fillRect( rect(), QBrush(m_defColor));
        p.setPen( QPen(m_defTextColor));
        p.drawText(0, 0, m_defText);
        return;
    }

    QString msg;
    if (Format::ADDRESS == m_format) {
        if (BOOL == m_valueType) {
            msg = QString("{%1.%2}").arg(m_regAddr).arg(m_bitAddr);
        }
        else if (INT == m_valueType) {
            msg = QString("{%1}").arg(m_regAddr);
        }
    }
    else if (Format::MESSAGE == m_format) {
        msg = QString("%1").arg(m_onText);
    }
        if (m_varValue.canConvert(QVariant::Bool) && BOOL == m_valueType) {
            m_varValue.toBool() ? msg = "TRUE" : msg = "FALSE";
        }
        else if (m_varValue.canConvert(QVariant::Int) && INT == m_valueType) {
            msg = QString("%1").arg(m_varValue.toInt());
        }
        else if (REAL == m_valueType) {
            msg = QString("%1").arg(m_varValue.toFloat());
        }
        else {
            msg = QString("%1").arg("Unknown");
        }
//    }

    p.fillRect(rect(), QBrush( m_onColor));
    p.setPen( QPen(m_onTextColor));
    QFont font;
    p.setFont(m_font);
    p.drawText(0, 0, this->width(), this->height(), Qt::AlignHCenter | Qt::AlignVCenter, msg);
}


void Indicator::drawIndicator()
{
}

