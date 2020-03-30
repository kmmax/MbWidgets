//#include "mblabelplugin.h"
#include "mbbuttonplugin.h"
#include "mbledplugin.h"
#include "mbmessageplugin.h"
#include "mbindicatorplugin.h"
#include "modbuswidgetcollection.h"

ModbusWidgetCollection::ModbusWidgetCollection(QObject *parent)
    : QObject(parent)
{
    m_widgets.append(new MbButtonPlugin(this));
    m_widgets.append(new MbLedPlugin(this));
    m_widgets.append(new MbMessagePlugin(this));
    m_widgets.append(new MbIndicatorPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> ModbusWidgetCollection::customWidgets() const
{
    return m_widgets;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(modbuswidgetcollectionplugin, ModbusWidgetCollection)
#endif // QT_VERSION < 0x050000
