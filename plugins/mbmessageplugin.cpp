#include "../widgets/message.h"
#include "mbmessageplugin.h"

#include <QtPlugin>

MbMessagePlugin::MbMessagePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void MbMessagePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool MbMessagePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *MbMessagePlugin::createWidget(QWidget *parent)
{
    return new Message(parent);
}

QString MbMessagePlugin::name() const
{
    return QLatin1String("Message");
}

QString MbMessagePlugin::group() const
{
    return QLatin1String("ModbusPlugin");
}

QIcon MbMessagePlugin::icon() const
{
    return QIcon(QLatin1String(":/greenLedOn.png"));
}

QString MbMessagePlugin::toolTip() const
{
    return QLatin1String("");
}

QString MbMessagePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool MbMessagePlugin::isContainer() const
{
    return false;
}

QString MbMessagePlugin::domXml() const
{
    return QLatin1String("<widget class=\"Message\" name=\"message\">\n</widget>\n");
}

QString MbMessagePlugin::includeFile() const
{
    return QLatin1String("../widgets/message.h");
}

