#include "../widgets/led.h"
#include "mbledplugin.h"

#include <QtPlugin>

MbLedPlugin::MbLedPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void MbLedPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool MbLedPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *MbLedPlugin::createWidget(QWidget *parent)
{
    return new Led(parent);
}

QString MbLedPlugin::name() const
{
    return QLatin1String("Led");
}

QString MbLedPlugin::group() const
{
    return QLatin1String("ModbusPlugin");
}

QIcon MbLedPlugin::icon() const
{
    return QIcon(QLatin1String(":/greenLedOn.png"));
}

QString MbLedPlugin::toolTip() const
{
    return QLatin1String("");
}

QString MbLedPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool MbLedPlugin::isContainer() const
{
    return false;
}

QString MbLedPlugin::domXml() const
{
    return QLatin1String("<widget class=\"Led\" name=\"led\">\n</widget>\n");
}

QString MbLedPlugin::includeFile() const
{
    return QLatin1String("../widgets/led.h");
}

