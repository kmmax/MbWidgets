#ifndef OISERVER_H
#define OISERVER_H

#include "mbwidget.h"
#include "mbbutton.h"

#include <QObject>
#include <QTimer>
#include <QVector>
#include <QSharedPointer>
#include <QList>
#include <QPair>

#include <memory>
#include <list>

// ---- IODriver ----
#include "../import/IODriverLib/includes/iodriverlib.h"

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <memory>
#include <exception>
// ---- IODriver ----

/*!
 * \brief Class represents modbus server for widgets
 *
 * \todo make checking QString ip address
 */
class OIServer : public QObject
{
    Q_OBJECT

public:
    using Range = QPair<quint16, quint16>;

    explicit OIServer(QObject *parent = nullptr);

    void setClientAddress(const QString &addr);
    QString clientAddress() { return m_clientAddr; }

    void addMbWidget(MbWidget* widget);
    void addMbWidgets(QList<MbWidget*> &widgets);
    void addMbButton(MbButton* button);
    void addMbButtons(QList<MbButton*> &buttons);
    void delMbWidget(MbWidget* widget);

    void start() { m_works = true;}
    void stop() { m_works = false;}
    bool isStart() { return m_works; }

    QVector<Range> ranges();

signals:

public slots:
    void updateQuality(bool quality);
    void cmdReceived(int cmd);
    void mbCmdReceived();

private slots:
    void updateTime();

private:
    const int DEFAULT_REQUESTS_INTERVAL = 100;              ///< interval between requests, ms
    const int DEFAULT_MODBUS_MAP_SIZE = 1000;               ///< size of modbus register's region
    const QString DEFAULT_CLIENT_ADDRESS = "127.0.0.1:10502"; ///< client's IP address

    std::list<MbWidget*> m_widget;     ///< Registered widgets
    std::list<MbButton*> m_buttons;
    MbData::Quality m_quality;
    bool m_works;                           ///< Flag, if server in process
    QTimer m_timer;
    QSharedPointer<MbData::MbRegisterMap> m_ptrRegisterMap;

    void notifyAll();                       ///< Sends data to all widgets
    void changeMbMap();                     ///< Updates modbus registers (emulator of external generator)

    //--- IODriver ---
    unique_ptr<IODriverLib> m_ptrLib;
    IDriver *m_ptrDrv;

    //--- Connection ---
    QString m_clientAddr;
    int m_requestDelay;
};

#endif // OISERVER_H
