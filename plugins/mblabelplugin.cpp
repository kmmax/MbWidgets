#include "../Widgets/mblabel.h"
#include "mblabelplugin.h"

#include <QtPlugin>

MbLabelPlugin::MbLabelPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void MbLabelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool MbLabelPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *MbLabelPlugin::createWidget(QWidget *parent)
{
    return new MbLabel(parent);
}

QString MbLabelPlugin::name() const
{
    return QLatin1String("MbLabel");
}

QString MbLabelPlugin::group() const
{
    return QLatin1String("ModbusPlugin");
}

QIcon MbLabelPlugin::icon() const
{
    return QIcon(QLatin1String(":/IndicatorAutoNo.png"));
}

QString MbLabelPlugin::toolTip() const
{
    return QLatin1String("");
}

QString MbLabelPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool MbLabelPlugin::isContainer() const
{
    return false;
}

QString MbLabelPlugin::domXml() const
{
    return QLatin1String("<widget class=\"MbLabel\" name=\"mbLabel\">\n</widget>\n");
}

QString MbLabelPlugin::includeFile() const
{
    return QLatin1String("../Widgets/mblabel.h");
}

