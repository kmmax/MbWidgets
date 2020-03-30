#include "../widgets/indicator.h"
#include "mbindicatorplugin.h"

#include <QtPlugin>

MbIndicatorPlugin::MbIndicatorPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void MbIndicatorPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool MbIndicatorPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *MbIndicatorPlugin::createWidget(QWidget *parent)
{
    return new Indicator(parent);
}

QString MbIndicatorPlugin::name() const
{
    return QLatin1String("Indicator");
}

QString MbIndicatorPlugin::group() const
{
    return QLatin1String("ModbusPlugin");
}

QIcon MbIndicatorPlugin::icon() const
{
    return QIcon(QLatin1String("qrc:/../resources/images/indicator.png"));
}

QString MbIndicatorPlugin::toolTip() const
{
    return QLatin1String("");
}

QString MbIndicatorPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool MbIndicatorPlugin::isContainer() const
{
    return false;
}

QString MbIndicatorPlugin::domXml() const
{
    return QLatin1String("<widget class=\"Indicator\" name=\"indicator\">\n</widget>\n");
}

QString MbIndicatorPlugin::includeFile() const
{
    return QLatin1String("../widgets/indicator.h");
}

