#include "spectogram.h"
#include "spectogrambuilder.h"
#include "monitorpluginfactory.h"
#include "version.h"

void CreateMonitorBuilder()
{
    MonitorPluginFactory::Get()->Register(new SpectogramBuilder());
}

wxString GetPluginName()
{
    return wxT("Specto");
}


wxString GetPluginVersion()
{
    return wxString::FromUTF8(AutoVersion::FULLVERSION_STRING);
}

wxString GetDetails()
{
    return wxT("Displays a Spectogram.\nThe x-axis is frequency.\nThe y-axis is time.\nThe colour reflects the amplitude from blue-cyan-green-yellow-red");
}
