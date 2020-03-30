#include "../widgets/mbbutton.h"
#include "mbbuttonplugin.h"

#include <QtPlugin>

MbButtonPlugin::MbButtonPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void MbButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool MbButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *MbButtonPlugin::createWidget(QWidget *parent)
{
    return new MbButton(parent);
}

QString MbButtonPlugin::name() const
{
    return QLatin1String("MbButton");
}

QString MbButtonPlugin::group() const
{
    return QLatin1String("ModbusPlugin");
}

QIcon MbButtonPlugin::icon() const
{
    return QIcon(QLatin1String(":/button.png"));
}

QString MbButtonPlugin::toolTip() const
{
    return QLatin1String("");
}

QString MbButtonPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool MbButtonPlugin::isContainer() const
{
    return false;
}

QString MbButtonPlugin::domXml() const
{
    return QLatin1String("<widget class=\"MbButton\" name=\"mbButton\">\n</widget>\n");
}

QString MbButtonPlugin::includeFile() const
{
    return QLatin1String("../widgets/mbbutton.h");
}

