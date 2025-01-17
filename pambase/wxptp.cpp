#include "wxptp.h"
#include "ptpmonkey.h"
#include "timedbuffer.h"
#include <wx/log.h>
#include "log.h"
#include "ptpeventhander.h"
#include "timeutils.h"
#include <iostream>
#include <iomanip>
#include "ptpclock.h"
#include "wxptpeventhandler.h"
#include "ptpeventloghandler.h"

wxDEFINE_EVENT(wxEVT_CLOCK_ADDED,wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CLOCK_UPDATED,wxCommandEvent);
wxDEFINE_EVENT(xEVT_CLOCK_REMOVED,wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CLOCK_TIME,wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CLOCK_MASTER,wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CLOCK_SLAVE,wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CLOCK_REMOVED,wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CLOCK_MSG_ANNOUNCE,wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CLOCK_MSG_SYNC,wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CLOCK_MSG_FOLLOWUP,wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CLOCK_MSG_DELAY_REQUEST,wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CLOCK_MSG_DELAY_RESPONSE,wxCommandEvent);


using namespace ptpmonkey;

void wxPtpEventHandler::AddHandler(wxEvtHandler* pHandler)
{
    m_lstHandlers.push_back(pHandler);
}

void wxPtpEventHandler::NotifyHandlers(wxEventType type, const wxString& sClockId)
{
    for(auto pHandler : m_lstHandlers)
    {
        wxCommandEvent* pEvent = new wxCommandEvent(type);
        pEvent->SetString(sClockId);
        wxQueueEvent(pHandler, pEvent);
    }
}

void wxPtpEventHandler::ClockAdded(std::shared_ptr<PtpV2Clock> pClock)
{
    NotifyHandlers(wxEVT_CLOCK_ADDED, wxString::FromUTF8(pClock->GetId().c_str()));
}

void wxPtpEventHandler::ClockUpdated(std::shared_ptr<PtpV2Clock> pClock)
{

    NotifyHandlers(wxEVT_CLOCK_UPDATED, wxString::FromUTF8(pClock->GetId().c_str()));
}

void wxPtpEventHandler::ClockBecomeMaster(std::shared_ptr<PtpV2Clock> pClock)
{
    NotifyHandlers(wxEVT_CLOCK_MASTER, wxString::FromUTF8(pClock->GetId().c_str()));
}

void wxPtpEventHandler::ClockBecomeSlave(std::shared_ptr<PtpV2Clock> pClock)
{
    NotifyHandlers(wxEVT_CLOCK_SLAVE, wxString::FromUTF8(pClock->GetId().c_str()));
}

void wxPtpEventHandler::ClockRemoved(std::shared_ptr<PtpV2Clock> pClock)
{
    NotifyHandlers(wxEVT_CLOCK_REMOVED, wxString::FromUTF8(pClock->GetId().c_str()));
}

void wxPtpEventHandler::ClockTimeCalculated(std::shared_ptr<PtpV2Clock> pClock)
{
    NotifyHandlers(wxEVT_CLOCK_TIME, wxString::FromUTF8(pClock->GetId().c_str()));
}

void wxPtpEventHandler::AnnounceSent(std::shared_ptr<PtpV2Clock> pClock)
{
    NotifyHandlers(wxEVT_CLOCK_MSG_ANNOUNCE, wxString::FromUTF8(pClock->GetId().c_str()));
}

void wxPtpEventHandler::SyncSent(std::shared_ptr<PtpV2Clock> pClock)
{
    NotifyHandlers(wxEVT_CLOCK_MSG_SYNC, wxString::FromUTF8(pClock->GetId().c_str()));
}

void wxPtpEventHandler::FollowUpSent(std::shared_ptr<PtpV2Clock> pClock)
{
    NotifyHandlers(wxEVT_CLOCK_MSG_FOLLOWUP, wxString::FromUTF8(pClock->GetId().c_str()));
}

void wxPtpEventHandler::DelayRequestSent(std::shared_ptr<PtpV2Clock> pClock)
{
    NotifyHandlers(wxEVT_CLOCK_MSG_DELAY_REQUEST, wxString::FromUTF8(pClock->GetId().c_str()));
}

void wxPtpEventHandler::DelayResponseSent(std::shared_ptr<PtpV2Clock> pClock)
{
    NotifyHandlers(wxEVT_CLOCK_MSG_DELAY_RESPONSE, wxString::FromUTF8(pClock->GetId().c_str()));
}





wxPtp& wxPtp::Get()
{
    static wxPtp ptp;
    return ptp;
}

wxPtp::wxPtp() : m_pNotifier(std::make_shared<wxPtpEventHandler>())
{
}

void wxPtp::RunDomain(const wxString& sInterface, unsigned char nDomain)
{
    auto itMonkey = m_mDomain.find(nDomain);
    if(itMonkey == m_mDomain.end())
    {
        itMonkey = m_mDomain.insert(std::make_pair(nDomain, std::make_shared<PtpMonkey>(IpInterface(std::string(sInterface.mb_str())), nDomain, 2))).first;
        itMonkey->second->AddEventHandler(m_pNotifier);
        //itMonkey->second->AddEventHandler(std::make_shared<ptpmonkey::PtpEventLogHandler>());
        itMonkey->second->Run();

    }
    else if(itMonkey->second->IsStopped())
    {
        itMonkey->second->Restart();
    }
}

void wxPtp::AddHandler(wxEvtHandler* pHandler)
{
    m_pNotifier->AddHandler(pHandler);
}

void wxPtp::StopDomain(unsigned char nDomain)
{
    auto itMonkey = m_mDomain.find(nDomain);
    if(itMonkey != m_mDomain.end())
    {
        itMonkey->second->Stop();
    }
}

std::shared_ptr<const PtpV2Clock> wxPtp::GetPtpClock(unsigned char nDomain, const wxString& sClockId)
{
    auto itMonkey = m_mDomain.find(nDomain);
    if(itMonkey != m_mDomain.end())
    {
        return itMonkey->second->GetClock(std::string(sClockId.mb_str()));
    }
    return nullptr;
}

bool wxPtp::IsSyncedToMaster(unsigned char nDomain) const
{
    auto itMonkey = m_mDomain.find(nDomain);
    return (itMonkey != m_mDomain.end() && itMonkey->second->IsSyncedToMaster());
}

void wxPtp::ResyncToMaster(unsigned char nDomain)
{
    auto itMonkey = m_mDomain.find(nDomain);
    if(itMonkey != m_mDomain.end())
    {
        itMonkey->second->ResyncToMaster();
    }
}

wxString wxPtp::GetMasterClockId(unsigned char nDomain)
{
    auto itMonkey = m_mDomain.find(nDomain);
    if(itMonkey != m_mDomain.end())
    {
        return wxString::FromUTF8(itMonkey->second->GetMasterClockId().c_str());
    }
    return wxEmptyString;
}

std::shared_ptr<const PtpV2Clock> wxPtp::GetSyncMasterClock(unsigned char nDomain)
{
    auto itMonkey = m_mDomain.find(nDomain);
    if(itMonkey != m_mDomain.end())
    {
        return itMonkey->second->GetSyncMasterClock();
    }
    return nullptr;
}

std::shared_ptr<const PtpV2Clock> wxPtp::GetLocalClock(unsigned char nDomain)
{
    auto itMonkey = m_mDomain.find(nDomain);
    if(itMonkey != m_mDomain.end())
    {
        return itMonkey->second->GetLocalClock();
    }
    return nullptr;
}

void wxPtp::ResetLocalClockStats(unsigned char nDomain)
{
    auto itMonkey = m_mDomain.find(nDomain);
    if(itMonkey != m_mDomain.end())
    {
        itMonkey->second->ResetLocalClockStats();
    }
}

timeval wxPtp::GetPtpTime(unsigned char nDomain)
{
    timeval tv;
    auto itMonkey = m_mDomain.find(nDomain);
    if(itMonkey != m_mDomain.end())
    {
        std::pair<std::chrono::seconds, std::chrono::nanoseconds> ptpTime = Split(itMonkey->second->GetPtpTime());
        tv.tv_sec = ptpTime.first.count();
        tv.tv_usec =ptpTime.second.count()/1000;
        return tv;
    }
    else
    {
        gettimeofday(&tv, nullptr);
        return tv;
    }
}

timespec wxPtp::GetPtpTimeSpec(unsigned char nDomain)
{
    timespec ts{0,0};
    auto itMonkey = m_mDomain.find(nDomain);
    if(itMonkey != m_mDomain.end())
    {

        std::pair<std::chrono::seconds, std::chrono::nanoseconds> ptpTime = Split(itMonkey->second->GetPtpTime());
        ts.tv_sec = ptpTime.first.count();
        ts.tv_nsec = ptpTime.second.count();
    }
    return ts;

}

std::map<std::string, std::shared_ptr<PtpV2Clock> >::const_iterator wxPtp::GetClocksBegin(unsigned char nDomain) const
{
    auto itMonkey = m_mDomain.find(nDomain);
    if(itMonkey != m_mDomain.end())
    {
        return itMonkey->second->GetClocksBegin();
    }
    else
    {
        return m_mEmpty.end();
    }
}

std::map<std::string, std::shared_ptr<PtpV2Clock> >::const_iterator wxPtp::GetClocksEnd(unsigned char nDomain) const
{
    auto itMonkey = m_mDomain.find(nDomain);
    if(itMonkey != m_mDomain.end())
    {
        return itMonkey->second->GetClocksEnd();
    }
    else
    {
        return m_mEmpty.end();
    }
}

timeval wxPtp::GetPtpOffset(unsigned char nDomain)
{
    timeval tv;
    auto itMonkey = m_mDomain.find(nDomain);
    if(itMonkey != m_mDomain.end())
    {

        std::pair<std::chrono::seconds, std::chrono::nanoseconds> ptpTime = Split(itMonkey->second->GetPtpOffset());
        tv.tv_sec = ptpTime.first.count();
        tv.tv_usec = ptpTime.second.count()/1000;
        return tv;
    }
    else
    {
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        return tv;
    }
}

timeval wxPtp::GetLastPtpOffset(unsigned char nDomain)
{
    timeval tv;
    auto itMonkey = m_mDomain.find(nDomain);
    if(itMonkey != m_mDomain.end())
    {

        std::pair<std::chrono::seconds, std::chrono::nanoseconds> ptpTime = Split(itMonkey->second->GetPtpOffset());
        tv.tv_sec = ptpTime.first.count();
        tv.tv_usec = ptpTime.second.count()/1000;
        return tv;
    }
    else
    {
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        return tv;
    }
}

