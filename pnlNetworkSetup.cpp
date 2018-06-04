#include "pnlNetworkSetup.h"
#include <wx/log.h>
#include "networkcontrol.h"
#include "dlgmask.h"

//(*InternalHeaders(pnlNetworkSetup)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(pnlNetworkSetup)
const long pnlNetworkSetup::ID_M_PBTN1 = wxNewId();
const long pnlNetworkSetup::ID_M_PLBL1 = wxNewId();
const long pnlNetworkSetup::ID_M_PLBL2 = wxNewId();
const long pnlNetworkSetup::ID_M_PLBL4 = wxNewId();
const long pnlNetworkSetup::ID_PANEL3 = wxNewId();
const long pnlNetworkSetup::ID_M_PKBD1 = wxNewId();
const long pnlNetworkSetup::ID_M_PLBL3 = wxNewId();
const long pnlNetworkSetup::ID_M_PBTN3 = wxNewId();
const long pnlNetworkSetup::ID_M_PLBL5 = wxNewId();
const long pnlNetworkSetup::ID_M_PBTN2 = wxNewId();
const long pnlNetworkSetup::ID_PANEL1 = wxNewId();
const long pnlNetworkSetup::ID_M_PSWP1 = wxNewId();
const long pnlNetworkSetup::ID_PANEL2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlNetworkSetup,wxPanel)
	//(*EventTable(pnlNetworkSetup)
	//*)
END_EVENT_TABLE()

pnlNetworkSetup::pnlNetworkSetup(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, long nStyle, const wxString& sEmpty)
{
	//(*Initialize(pnlNetworkSetup)
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	SetBackgroundColour(wxColour(0,0,0));
	m_pbtnStaticDHCP = new wmButton(this, ID_M_PBTN1, _("Type"), wxPoint(0,40), wxSize(200,40), wmButton::STYLE_SELECT, wxDefaultValidator, _T("ID_M_PBTN1"));
	m_pbtnStaticDHCP->SetBackgroundColour(wxColour(0,128,192));
	m_pLbl1 = new wmLabel(this, ID_M_PLBL1, _("IP Address"), wxPoint(0,85), wxSize(100,40), 0, _T("ID_M_PLBL1"));
	m_pLbl1->SetBorderState(uiRect::BORDER_NONE);
	m_pLbl1->SetForegroundColour(wxColour(255,255,255));
	m_pLbl1->SetBackgroundColour(wxColour(64,0,128));
	m_pLbl2 = new wmLabel(this, ID_M_PLBL2, _("Subnet Mask"), wxPoint(0,130), wxSize(100,40), 0, _T("ID_M_PLBL2"));
	m_pLbl2->SetBorderState(uiRect::BORDER_NONE);
	m_pLbl2->SetForegroundColour(wxColour(255,255,255));
	m_pLbl2->SetBackgroundColour(wxColour(64,0,128));
	m_pLbl4 = new wmLabel(this, ID_M_PLBL4, _("Gateway"), wxPoint(0,175), wxSize(100,40), 0, _T("ID_M_PLBL4"));
	m_pLbl4->SetBorderState(uiRect::BORDER_NONE);
	m_pLbl4->SetForegroundColour(wxColour(255,255,255));
	m_pLbl4->SetBackgroundColour(wxColour(64,0,128));
	m_ppnlGateway = new wmipeditpnl(this, ID_PANEL3, wxPoint(100,175), wxSize(200,40), wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	m_ppnlGateway->SetForegroundColour(wxColour(0,0,0));
	m_ppnlGateway->SetBackgroundColour(wxColour(255,255,255));
	m_pkbd = new wmKeyboard(this, ID_M_PKBD1, wxPoint(10,230), wxSize(240,200), 5, 0);
	m_pkbd->SetForegroundColour(wxColour(255,255,255));
	wxFont m_pkbdFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	m_pkbd->SetFont(m_pkbdFont);
	m_pLbl3 = new wmLabel(this, ID_M_PLBL3, _("Manage Network Settings"), wxPoint(0,5), wxSize(600,30), 0, _T("ID_M_PLBL3"));
	m_pLbl3->SetBorderState(uiRect::BORDER_NONE);
	m_pLbl3->SetForegroundColour(wxColour(255,255,255));
	m_pLbl3->SetBackgroundColour(wxColour(0,64,0));
	wxFont m_pLbl3Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	m_pLbl3->SetFont(m_pLbl3Font);
	m_pbtnMask = new wmButton(this, ID_M_PBTN3, wxEmptyString, wxPoint(100,130), wxSize(200,40), 0, wxDefaultValidator, _T("ID_M_PBTN3"));
	m_pbtnMask->SetForegroundColour(wxColour(0,0,0));
	m_pbtnMask->SetBackgroundColour(wxColour(255,255,255));
	m_pbtnMask->SetColourDisabled(wxColour(wxT("#909090")));
	m_pSwp1 = new wmSwitcherPanel(this, ID_M_PSWP1, wxPoint(310,85), wxSize(280,340), wmSwitcherPanel::STYLE_NOSWIPE|wmSwitcherPanel::STYLE_NOANIMATION, _T("ID_M_PSWP1"));
	m_pSwp1->SetPageNameStyle(0);
	Panel1 = new wxPanel(m_pSwp1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	Panel1->SetBackgroundColour(wxColour(0,0,0));
	m_plblResult = new wmLabel(Panel1, ID_M_PLBL5, _("Gateway"), wxPoint(0,145), wxSize(280,200), 0, _T("ID_M_PLBL5"));
	m_plblResult->SetBorderState(uiRect::BORDER_NONE);
	m_plblResult->SetForegroundColour(wxColour(255,0,0));
	m_plblResult->SetBackgroundColour(wxColour(0,0,0));
	wxFont m_plblResultFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	m_plblResult->SetFont(m_plblResultFont);
	m_plblResult->SetTextAlign(wxALIGN_LEFT | wxALIGN_TOP);
	m_pbtnApply = new wmButton(Panel1, ID_M_PBTN2, _("Apply"), wxPoint(0,90), wxSize(100,40), 0, wxDefaultValidator, _T("ID_M_PBTN2"));
	m_pSwp1->AddPage(Panel1, _("Page1"), false);
	m_ppnlAddress = new wmipeditpnl(this, ID_PANEL2, wxPoint(100,85), wxSize(200,40), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	m_ppnlAddress->SetForegroundColour(wxColour(0,0,0));
	m_ppnlAddress->SetBackgroundColour(wxColour(255,255,255));

	Connect(ID_M_PBTN1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlNetworkSetup::OntnStaticDHCPClick);
	Connect(ID_M_PBTN3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlNetworkSetup::OnbtnMaskClick);
	//*)
	Connect(ID_M_PBTN2, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&pnlNetworkSetup::OnbtnApplyClick);



	m_pbtnStaticDHCP->SetToggleLook(true, wxT("Static"), wxT("DHCP"), 40);


    m_pkbd->SetReturnString(wxT("-->|"));
	SetSize(size);
	SetPosition(pos);

    bool bDHCP((NetworkControl::Get().GetAddress() == wxEmptyString));
	m_pbtnStaticDHCP->ToggleSelection(bDHCP, true);

	m_ppnlAddress->SetValue(NetworkControl::Get().GetAddress());
	m_ppnlGateway->SetValue(NetworkControl::Get().GetGateway());

    m_pbtnMask->SetLabel(wxString::Format(wxT("/%d (%s)"), NetworkControl::Get().GetMask(), NetworkControl::Get().ConvertMaskToAddress(NetworkControl::Get().GetMask())));


}

pnlNetworkSetup::~pnlNetworkSetup()
{
	//(*Destroy(pnlNetworkSetup)
	//*)
}


void pnlNetworkSetup::OntnStaticDHCPClick(wxCommandEvent& event)
{
    m_ppnlAddress->Enable((event.IsChecked() == false));
    m_pbtnMask->Enable((event.IsChecked() == false));
    m_ppnlGateway->Enable((event.IsChecked() == false));
    m_pkbd->Enable((event.IsChecked() == false));

    if(event.IsChecked())
    {
        m_ppnlAddress->SetValue(wxEmptyString);
        m_pbtnMask->SetLabel(wxEmptyString);
        m_ppnlGateway->SetValue(wxEmptyString);
        m_pLbl1->SetBackgroundColour(wxColour(128,128,128));
        m_pLbl2->SetBackgroundColour(wxColour(128,128,128));
        m_pLbl4->SetBackgroundColour(wxColour(128,128,128));
    }
    else
    {
        m_ppnlAddress->SetFocus();
        m_pLbl1->SetBackgroundColour(wxColour(64,0,128));
        m_pLbl2->SetBackgroundColour(wxColour(64,0,128));
        m_pLbl4->SetBackgroundColour(wxColour(64,0,128));
    }
}

void pnlNetworkSetup::OnedtAddressTextEnter(wxCommandEvent& event)
{

}

void pnlNetworkSetup::OnedtSubnetTextEnter(wxCommandEvent& event)
{
    m_ppnlGateway->SetFocus();
}

void pnlNetworkSetup::OnedtGatewayText(wxCommandEvent& event)
{

}

void pnlNetworkSetup::OnbtnApplyClick(wxCommandEvent& event)
{
    unsigned long nMask(0);
    m_pbtnMask->GetLabel().AfterFirst(wxT('/')).BeforeFirst(wxT(' ')).ToULong(&nMask);
    //m_pchMask->GetString(m_pchMask->GetSelection()).AfterFirst(wxT('/')).BeforeFirst(wxT(' ')).ToULong(&nMask);
    m_plblResult->SetLabel(NetworkControl::Get().SetupNetworking(m_ppnlAddress->GetValue(), nMask, m_ppnlGateway->GetValue()));

}

void pnlNetworkSetup::OnbtnCancelClick(wxCommandEvent& event)
{
}

void pnlNetworkSetup::OnedtGatewayTextEnter(wxCommandEvent& event)
{
    m_ppnlAddress->SetFocus();
}

void pnlNetworkSetup::OnbtnMaskClick(wxCommandEvent& event)
{

    dlgMask aDlg(this, m_pbtnMask->GetLabel(), wxNewId(), ClientToScreen(m_pbtnMask->GetPosition()));
    if(aDlg.ShowModal()== wxID_OK)
    {
        m_pbtnMask->SetLabel(aDlg.m_sSelected);
        m_ppnlGateway->SetFocus();
    }
}

