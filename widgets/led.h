#ifndef LED_H
#define LED_H

#include "mbwidget.h"


#include <QWidget>


class Led : public MbWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor onColor READ onColor WRITE setOnColor)
    Q_PROPERTY(QColor offColor READ offColor WRITE setOffColor)
    Q_PROPERTY(QColor undefColor READ undefColor WRITE setUndefColor)

public:
    Led(QWidget *parent = nullptr);
    Led(const Led& led, QWidget *parent = nullptr);
    virtual ~Led() override = default;

    // MbWidget interface
    QColor onColor() const { return m_onColor; }
    QColor offColor() const { return m_offColor; }
    QColor undefColor() const { return m_undefColor; }

public slots:
    void setOnColor(const QColor &onColor);
    void setOffColor(const QColor &offColor);
    void setUndefColor(const QColor &undefColor);

signals:


protected:
    void onWidgetUpdate() override;
    void mousePressEvent(QMouseEvent *event) override;
    // QWidget interface
    void paintEvent(QPaintEvent *event) override;

private:
    QColor m_onColor;
    QColor m_offColor;          ///< Color for switched off state
    QColor m_undefColor;        ///< Color when state isn't defined

    void initGraphicSystem(QPainter &painter);
    void drawFlatCycle();
    void drawHighlightCycle();

    // QWidget interface
protected:
    QPixmap *m_background;
    QPixmap * m_pixmap;


};

// To use Q_DECLARE_METATYPE, we need:
// - default constructor;
// - constructor of copy;
// - virtual destructor
Q_DECLARE_METATYPE(Led)


#endif // LED_H
