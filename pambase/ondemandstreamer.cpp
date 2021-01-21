#include "ondemandstreamer.h"
#include "PamTaskScheduler.h"
#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"
#include <thread>
#include <wx/log.h>
#include "PamUsageEnvironment.h"
#include "GroupsockHelper.hh"
#include <chrono>
#include <iomanip>
#include <sstream>
#include "ondemandpamsubsession.h"
#include "log.h"

wxDEFINE_EVENT(wxEVT_ODS_ANNOUNCE, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_ODS_CONNECTION, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_ODS_DISCONNECTION, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_ODS_FINISHED, wxCommandEvent);




OnDemandStreamer::OnDemandStreamer(wxEvtHandler* pHandler, const wxString& sRTSPAddress, unsigned short nRtspPort) :
    m_pHandler(pHandler),
    m_sRtspAddress(sRTSPAddress),
    m_nRtspPort(nRtspPort),
    m_pSubsession(nullptr),
    m_eventLoopWatchVariable(0),
    m_pSMS(nullptr)
{
    // Begin by setting up our usage environment:
    m_pScheduler = PamTaskScheduler::createNew();
    m_pEnv = PamUsageEnvironment::createNew(*m_pScheduler,nullptr);
}



void* OnDemandStreamer::Entry()
{
    // Create the RTSP server:
//    SendingInterfaceAddr = our_inet_addr(std::string(m_sRtspAddress.mb_str()).c_str());

    RTSPServer* rtspServer = RTSPServer::createNew(*m_pEnv, m_nRtspPort, NULL);
    if (rtspServer == NULL)
    {
        pml::Log::Get(pml::Log::LOG_ERROR) << "Failed to create RTSP server: " << m_pEnv->getResultMsg() << std::endl;
        SendFinish();
        return NULL;
    }

    if(m_pSubsession == nullptr)
    {
        SendFinish();
        return NULL;
    }

    char const* descriptionString = wxGetHostName().c_str() + " PAM_"+m_pSubsession->GetStreamName();
    std::string sStreamName = "by-name/PAM_"+m_pSubsession->GetStreamName();

    pml::Log::Get(pml::Log::LOG_DEBUG) << "StreamName = '" << sStreamName << "'" << std::endl;

    m_pSMS = ServerMediaSession::createNew(*m_pEnv, sStreamName.c_str(), sStreamName.c_str(), descriptionString);
    m_pSMS->addSubsession(m_pSubsession);
    rtspServer->addServerMediaSession(m_pSMS);


    AnnounceStream(rtspServer, m_pSMS, sStreamName);

    //GetSDP();

    // Also, attempt to create a HTTP server for RTSP-over-HTTP tunneling.
    // Try first with the default HTTP port (80), and then with the alternative HTTP
    // port numbers (8000 and 8080).

    if (rtspServer->setUpTunnelingOverHTTP(80) || rtspServer->setUpTunnelingOverHTTP(8000) || rtspServer->setUpTunnelingOverHTTP(8080))
    {
        pml::Log::Get(pml::Log::LOG_INFO) << "(We use port " << rtspServer->httpServerPortNum() << " for optional RTSP-over-HTTP tunneling.)" << std::endl;
    }
    else
    {
        pml::Log::Get(pml::Log::LOG_WARN) << "(RTSP-over-HTTP tunneling is not available.)" << std::endl;
    }


    while(m_eventLoopWatchVariable == 0)
    {
        m_pEnv->taskScheduler().doEventLoop(&m_eventLoopWatchVariable);
    }

    Medium::close(rtspServer);

    SendFinish();
    return NULL;
}

void OnDemandStreamer::SendFinish()
{
    wxCommandEvent* pEvent = new wxCommandEvent(wxEVT_ODS_FINISHED);
    wxQueueEvent(m_pHandler, pEvent);
}

void OnDemandStreamer::Stop()
{
    m_eventLoopWatchVariable = 1;
}

void OnDemandStreamer::AnnounceStream(RTSPServer* rtspServer, ServerMediaSession* sms,  const std::string& sStreamName)
{
    char* url = rtspServer->rtspURL(sms);


    UsageEnvironment& env = rtspServer->envir();
    pml::Log::Get(pml::Log::LOG_INFO) << "\"" << sStreamName << "\" stream" << std::endl;
    pml::Log::Get(pml::Log::LOG_INFO) << "Play this stream using the URL \"" << url << "\"" << std::endl;

    if(m_pHandler)
    {
        wxCommandEvent* pEvent = new wxCommandEvent(wxEVT_ODS_ANNOUNCE);
        pEvent->SetString(wxString::FromUTF8(url));
        wxQueueEvent(m_pHandler, pEvent);
    }

    delete[] url;
}


const std::string& OnDemandStreamer::GetSDP()
{
    /*
    if(m_sSDP.empty())
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> tp(std::chrono::high_resolution_clock::now());
        unsigned long nSeconds = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count();
        auto nMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(tp.time_since_epoch()).count();
        nMicroseconds %= 1000000;
        std::stringstream ss;
        ss << "v=0\r\n"
           << "o=- " << nSeconds << std::setw(6) << std::setfill('0') << nMicroseconds << " 1 IN IP4 " << m_sRtspAddress << "\r\n"
          << std::setw(0)
           << "s=" << wxGetHostName().c_str() + "_PAM\r\n"
           << "i=" << "Unicast Stream" << "\r\n"
           << "t=0 0\r\n"
           << "a=type:broadcast\r\n"
           << "a=control:*\r\n"
           << m_pSubsession->GetSDP();


           m_sSDP = ss.str();
    }
    */
    return m_sSDP;
}
