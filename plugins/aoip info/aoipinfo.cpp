#include "aoipinfo.h"
#include "aoipinfobuilder.h"
#include "monitorpluginfactory.h"
#include "version.h"

void CreateMonitorBuilder()
{
    MonitorPluginFactory::Get()->Register(new AoIPInfoBuilder());
}


wxString GetPluginName()
{
    return wxT("Session Info");

}


wxString GetPluginVersion()
{
    return wxString::FromUTF8(AutoVersion::FULLVERSION_STRING);
}

wxString GetDetails()
{
    return wxT("Displays details about RTP sessions and QoS.");
}
