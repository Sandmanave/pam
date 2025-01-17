#include "pnlrouting.h"

//(*InternalHeaders(pnlRouting)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include "radarbuilder.h"

//(*IdInit(pnlRouting)
const long pnlRouting::ID_M_PLST3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlRouting,wxPanel)
	//(*EventTable(pnlRouting)
	//*)
END_EVENT_TABLE()

pnlRouting::pnlRouting(wxWindow* parent,RadarBuilder* pBuilder, wxWindowID id,const wxPoint& pos,const wxSize& size) :
    m_pBuilder(pBuilder)
{
	//(*Initialize(pnlRouting)
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	SetBackgroundColour(wxColour(0,0,0));
	m_plstFFT_Routing = new wmList(this, ID_M_PLST3, wxPoint(0,0), wxSize(190,200), wmList::STYLE_SELECT, 0, wxSize(-1,-1), 2, wxSize(5,5));
	m_plstFFT_Routing->SetBackgroundColour(wxColour(0,0,0));

	Connect(ID_M_PLST3,wxEVT_LIST_SELECTED,(wxObjectEventFunction)&pnlRouting::OnlstFFT_RoutingSelected);
	//*)




}

pnlRouting::~pnlRouting()
{
	//(*Destroy(pnlRouting)
	//*)
}

void pnlRouting::SetNumberOfChannels(unsigned int nChannels)
{
    m_plstFFT_Routing->Freeze();
    m_plstFFT_Routing->Clear();

    if(nChannels == 2)
    {
        m_plstFFT_Routing->AddButton(wxT("Left"), wxNullBitmap, (void*)0);
        m_plstFFT_Routing->AddButton(wxT("Right"), wxNullBitmap, (void*)1);
        m_plstFFT_Routing->AddButton(wxT("Middle"), wxNullBitmap, (void*)9);
        m_plstFFT_Routing->AddButton(wxT("Side"), wxNullBitmap, (void*)10);
    }
    else
    {
        for(unsigned int i = 0; i < nChannels; i++)
        {
            m_plstFFT_Routing->AddButton(wxString::Format(wxT("Channel %d"), i+1), wxNullBitmap, (void*)i);
        }
    }


    m_plstFFT_Routing->SelectButton(m_plstFFT_Routing->FindButton((void*)m_pBuilder->ReadSetting(wxT("Routing"),0)), true);
    m_plstFFT_Routing->Thaw();
}

void pnlRouting::OnlstFFT_RoutingSelected(wxCommandEvent& event)
{
    m_pBuilder->WriteSetting(wxT("Routing"), (int)(event.GetClientData()));
}
