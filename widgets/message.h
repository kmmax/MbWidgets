#ifndef MESSAGE_H
#define MESSAGE_H

#include "mbwidget.h"

#include <QLabel>
#include <QTimer>

class Message : public MbWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor onColor READ onColor WRITE setOnColor)   // Text color when undefined state
    Q_PROPERTY(QColor onTextColor READ onTextColor WRITE setOnTextColor)   // Text color when undefined state
    Q_PROPERTY(QString onText READ onText WRITE setOnText)

    Q_PROPERTY(QColor offColor READ offColor WRITE setOffColor)   // Background color when undefined state
    Q_PROPERTY(QColor offTextColor READ offTextColor WRITE setOffTextColor)   // Background color when undefined state
    Q_PROPERTY(QString offText READ offText WRITE setOffText)

    Q_PROPERTY(QColor defColor READ defColor WRITE setDefColor)   // Background color when undefined state
    Q_PROPERTY(QColor defTextColor READ defTextColor WRITE setDefTextColor)
    Q_PROPERTY(QString defText READ defText WRITE setDefText)                 // Text when undefined state
    Q_PROPERTY(bool flash READ flash WRITE setFlash)

public:
    Message(QWidget *parent = nullptr);
    Message(const Message& message, QWidget *parent = nullptr);
    Message& operator=(const Message& message);
    virtual ~Message() override = default;

    QColor onColor() const { return m_onColor; }
    QColor onTextColor() const { return m_onTextColor; }
    QString onText() const { return m_onText; }
    QColor offColor() const { return m_offColor; }
    QColor offTextColor() const { return m_offTextColor; }
    QString offText() const { return m_offText; }
    QColor defColor() const { return m_defColor; }
    QString defText() const { return m_defText; }
    QColor defTextColor() const { return m_defTextColor; }

    bool flash() const { return m_flash; }

signals:

public slots:
    void setOnColor(QColor color) { m_onColor = color; update(); }
    void setOnTextColor(QColor onTextColor) { m_onTextColor = onTextColor; }
    void setOffColor(QColor color) { m_offColor = color; update(); }
    void setDefText(QString color) { m_defText = color; update(); }
    void setOnText(QString onText) { m_onText = onText; update(); }
    void setOffText(QString offText) { m_offText = offText; update(); }
    void setDefColor(QColor defColor) { m_defColor = defColor; }
    void setFlash(bool flash) { m_flash = flash; changeTimerState(m_flash); }
    void setOffTextColor(QColor offTextColor) { m_offTextColor = offTextColor; }
    void setDefTextColor(QColor defTextColor) { m_defTextColor = defTextColor; }

private:
    bool m_flash;

    QTimer *m_timer;

    void timerTimeout();
    bool changeTimerState(bool flash);

    QColor m_onColor;
    QColor m_onTextColor;
    QString m_onText;

    QColor m_offColor;
    QColor m_offTextColor;
    QString m_offText;

    QColor m_defColor;
    QColor m_defTextColor;
    QString m_defText;

    bool m_tick = false;

    void drawRectangle();
    void drawMessage();

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
Q_DECLARE_METATYPE(Message)

#endif // MESSAGE_H
