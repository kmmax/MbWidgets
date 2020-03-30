#include "led.h"


Led::Led(QWidget *parent) : MbWidget(parent)
{
    m_background = new QPixmap();
    m_onColor = QColor(Qt::red);
    m_offColor = QColor(Qt::green);
    m_pixmap = new QPixmap(size());
}


Led::Led(const Led &led, QWidget *parent) : MbWidget(parent)
{
    m_onColor = led.onColor();
}


void Led::setOnColor(const QColor &onColor)
{
    if (m_onColor == onColor)
        return;

    m_onColor = onColor;
    update();
}


void Led::setOffColor(const QColor &offColor) {
    if (m_offColor == offColor)
        return;

    m_offColor = offColor;
    update();
}


void Led::setUndefColor(const QColor &undefColor)
{
    if (m_undefColor == undefColor)
        return;

    m_undefColor = undefColor;
    update();
}


void Led::onWidgetUpdate()
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


void Led::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if (nullptr == m_ptrMbRegisterMap) {
        qDebug() << "MbWidget: MbRegisterMap ins't defined";
        return;
    }

    Q_ASSERT(m_cmdAddr <= m_ptrMbRegisterMap->size());

    (*m_ptrMbRegisterMap)[m_cmdAddr].value = m_cmdCode;

    emit cmdActivated();
}


void Led::drawHighlightCycle()
{
    if (m_pixmap->size() != size()) {
        delete m_pixmap;
        m_pixmap = new QPixmap(size());
        m_pixmap->fill(QColor(0,0,0,0));
        QPainter painter(m_pixmap);

        initGraphicSystem(painter);
        painter.setPen(Qt::NoPen);
        QRadialGradient shine(QPointF(-40.0,-40.0),120.0, QPointF(-40,-40));
        QColor white1(255,255,255,200);
        QColor white0(255,255,255,0);

        shine.setColorAt(0.0,white1);
        shine.setColorAt(1.0,white0);

        painter.setBrush(shine);
        painter.drawEllipse(-147,-147,297,297);
    }
    QPainter painter(this);
    painter.drawPixmap(0,0, *m_pixmap);
}


void Led::initGraphicSystem(QPainter &painter)
{
    int side = qMin(width(), height());
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 330.0, side / 330.0);
}


void Led::drawFlatCycle()
{
    QPainter painter(this);
    initGraphicSystem(painter);

    // draw cicle
    QColor brushColor = m_offColor;
    m_quality = MbData::Quality::Good;	// Debug
    if (MbData::Quality::Good == m_quality)
        if (BOOL == m_valueType) {
            m_varValue.toBool()? brushColor=m_onColor : brushColor=m_offColor;
        }
    else
        brushColor = m_undefColor;
    painter.setBrush(brushColor);

    QColor penColor;
    penColor = brushColor;
    QPen pen;
    pen.setColor(penColor);
    pen.setWidthF(3.0);

    painter.drawEllipse(-149,-149,299,299);
    painter.end();
}


void Led::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    drawFlatCycle();
    drawHighlightCycle();
}
