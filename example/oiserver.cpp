#include "oiserver.h"

#include <QDebug>


OIServer::OIServer(QObject *parent) : QObject(parent),
    m_quality(MbData::Quality::Good),
    m_works(false),
    m_clientAddr(DEFAULT_CLIENT_ADDRESS),
    m_requestDelay(DEFAULT_REQUESTS_INTERVAL)
{
    qDebug() << "IOServer constructor";
    //--- IODriver ----
    m_ptrLib = std::make_unique<IODriverLib>();
    m_ptrDrv =  m_ptrLib->createDriver("Modbus");

    if (IDriver::Config::Ok != m_ptrDrv->setComConfigure(m_clientAddr.toStdString()))
        cout << "Bad Com config" << endl;

    if (IDriver::Config::Ok != m_ptrDrv->setDataConfigure("{0,10}"))
        cout << "Bad data config" << endl;

    cout << "Driver: " << m_ptrDrv->name() << endl;
    if (m_ptrDrv->setRequestDelay(m_requestDelay))
    m_ptrDrv->start();

    // internal modbus register's map
    m_ptrRegisterMap = QSharedPointer<MbData::MbRegisterMap>::create(MbData::MbRegisterMap(DEFAULT_MODBUS_MAP_SIZE));
//    m_ptrRegisterMap->resize(MODBUS_MAP_SIZE);
    qDebug() << "OIServer: MbRegisterMap has created (size=" << m_ptrRegisterMap->size() << ")";

    // cyclic interval of updating
    m_timer.setInterval(DEFAULT_REQUESTS_INTERVAL);
    connect(&m_timer, &QTimer::timeout, this, &OIServer::updateTime);
    m_timer.start();
}


void OIServer::setClientAddress(const QString &addr) {
    qDebug() << "setClientAddress " << addr;
    m_clientAddr = addr;
    Q_ASSERT(nullptr != m_ptrDrv);

    if (IDriver::Config::Ok != m_ptrDrv->setComConfigure(m_clientAddr.toStdString()))
        cout << "Bad Com config" << endl;

    std::cout << m_ptrDrv->comConfigure();
}


/*!
 * \brief Registers widget
 * \param[in] indicator
 */
void OIServer::addMbWidget(MbWidget *widget)
{
    widget->setMbRegisterMap(m_ptrRegisterMap);
    connect(widget, &MbWidget::cmdActivated, this, &OIServer::mbCmdReceived);
    m_widget.push_back(widget);
}


void OIServer::addMbWidgets(QList<MbWidget *> &widgets)
{
    for (auto widget: widgets) {
//        qDebug() << "\t" << widget->objectName();
        this->addMbWidget(widget);
//        m_oiserver.addMbWidget(widget);
    }
}


void OIServer::addMbButton(MbButton *button)
{
    button->setMbRegisterMap(m_ptrRegisterMap);
    connect(button, &MbButton::cmdValueChanged, this, &OIServer::cmdReceived);
    m_buttons.push_back(button);
}


void OIServer::addMbButtons(QList<MbButton *> &buttons)
{
    for (auto button: buttons) {
//        qDebug() << "\t" << button->objectName();
        this->addMbButton(button);
    }

}


/*!
 * \brief Unregisters widget
 * \param[in] indicator
 */
void OIServer::delMbWidget(MbWidget *widget)
{
    m_widget.remove(widget);
}


QVector<OIServer::Range> OIServer::ranges()
{
    QVector<OIServer::Range> ranges;
//    for (auto &wgt: m_widget) {
//        ranges.push_back(OIServer::Range(wgt->regAddr(), 10));
//    }

    // dummy
    ranges.push_back({10, 21});
    ranges.push_back({3121, 3200});
    return ranges;
}


/*!
 * \brief Notifies all registered widgets
 *
 * \todo make method more properly
 */
void OIServer::notifyAll()
{
    if (m_works) {
        for (auto indicator: m_widget)  {
            indicator->onDataUpdated();
        }
    }
}


/*!
 * \brief Changes register's values
 *
 * \brief Increase each register in modbus map (first MAX_NUMBER registers)
 */
void OIServer::changeMbMap()
{
    const quint16 MAX_VALUE_NUMBER = 255;
    const quint16 NUMBER_REGISTERS = 125;

    Q_ASSERT(DEFAULT_MODBUS_MAP_SIZE > NUMBER_REGISTERS);

    // MbRegisterMap filling
    std::vector<IDriver::Data> datas = m_ptrDrv->readDatas();

    MbData::MbRegisterMap::Iterator it = m_ptrRegisterMap->begin();
    for (; it!=m_ptrRegisterMap->end(); it++) {

        std::vector<IDriver::Data> datas = m_ptrDrv->readDatas();
        Q_ASSERT(datas.size()>0);
        auto data = datas.at(0);
        it->direct = MbData::Register::Direction::r;
        it->qulity = MbData::Quality::Good;
    }
    for (auto &data: datas) {
        Q_ASSERT(data.addr+data.regs.size() <= m_ptrRegisterMap->size());
        for (unsigned int i=0; i<data.regs.size(); i++) {
            auto addr = data.addr+i;
            (*m_ptrRegisterMap)[addr].value = data.regs.at(i);
//            (*m_ptrRegisterMap)[addr].qulity = data.quality;
        }
    }


//    while(true) {
//        std::this_thread::sleep_for(std::chrono::seconds(1));
//        std::vector<IDriver::Data> datas = drv->readDatas();
//        std::cout << "Number of ranges: " << datas.size() << endl;
//        for (auto &data: datas) {
//            cout << "[addr=" << data.addr << ", number=" << data.regs.size() << "] : ";

//            for (uint16_t addr=data.addr; addr<data.addr+data.regs.size(); addr++) {
//                    std::cout << data.regs.at(addr-data.addr) << " ";
//                }
//            cout << "(" << data.quality_to_string(data.quality) << ")" << endl;
//        }
//        cout << endl;
//    }
}


/*!
 * \brief Changes quality
 * \param[in] quality - (true - good quality)
 */
void OIServer::updateQuality(bool quality)
{
    if (quality)
        m_quality = MbData::Quality::Good;
    else
        m_quality = MbData::Quality::NoConnect;
    notifyAll();
}


void OIServer::cmdReceived(int cmd)
{
    MbButton* senderPointer = qobject_cast<MbButton*>(sender());
    if(senderPointer == nullptr)
        qDebug() << "1: Sender isn't MbButton";
    else {
        qDebug() << "1: Sender: " << senderPointer->cmdAddress() << "; " << cmd;
        m_ptrDrv->write(senderPointer->cmdAddress(), cmd);
    }
}


void OIServer::mbCmdReceived()
{
    MbWidget* senderPointer = qobject_cast<MbWidget*>(sender());
    if(senderPointer == nullptr)
        qDebug() << "2: Sender isn't MbWidget";
    else
        qDebug() << "2: Sender: " << senderPointer->cmdAddr() << "; " << senderPointer->cmdCode();
}


/*!
 * \brief Timer's timeout
 */
void OIServer::updateTime()
{
    changeMbMap();
    notifyAll();
}
