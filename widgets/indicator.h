#ifndef INDICATOR_H
#define INDICATOR_H

#include "mbwidget.h"

#include <QLabel>
#include <QTimer>

class Indicator : public MbWidget
{
    Q_OBJECT
    Q_ENUMS(Format)

    Q_PROPERTY(Format format READ format WRITE setFormat NOTIFY formatChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont)

    Q_PROPERTY(QColor backColor READ backColor WRITE setOnColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setOnTextColor)
    Q_PROPERTY(QString text READ text WRITE setOnText)

public:
    enum Format {
        VALUE,
        ADDRESS,
        MESSAGE
    };

    Indicator(QWidget *parent = nullptr);
    Indicator(const Indicator& indicator, QWidget *parent = nullptr);
    Indicator& operator=(const Indicator& indicator);
    virtual ~Indicator() override = default;

    QColor backColor() const { return m_onColor; }
    QColor textColor() const { return m_onTextColor; }
    QString text() const { return m_onText; }

    Format format() const { return m_format; }

    QFont font() const { return m_font; }

signals:

    void formatChanged(Format format);

public slots:
    void setOnColor(QColor color) { m_onColor = color; update(); }
    void setOnTextColor(QColor onTextColor) { m_onTextColor = onTextColor; }
    void setDefText(QString color) { m_defText = color; update(); }
    void setOnText(QString onText) { m_onText = onText; update(); }

    void setFormat(Format format);
    void setFont(QFont font) { m_font = font; }

private:
    bool m_flash;

    QTimer *m_timer;

    void timerTimeout();
    bool m_tick = false;
    bool changeTimerState(bool flash);

    QColor m_onColor;
    QColor m_onTextColor;
    QString m_onText;

//    QColor m_offColor;
//    QColor m_offTextColor;
//    QString m_offText;

    QColor m_defColor;
    QColor m_defTextColor;
    QString m_defText;

    Format m_format;
    QFont m_font;

    void drawRectangle();
    void drawIndicator();

protected:
    void onWidgetUpdate() override;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *) override;
};

// To use Q_DECLARE_METATYPE, we need:
// - default constructor;
// - constructor of copy;
// - virtual destructor
Q_DECLARE_METATYPE(Indicator)

#endif // INDICATOR_H
