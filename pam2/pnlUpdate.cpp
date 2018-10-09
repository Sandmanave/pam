#include "pnlUpdate.h"

//(*InternalHeaders(pnlUpdate)
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include "settings.h"
#include <wx/dir.h>
#include "folder.xpm"
#include <wx/log.h>

#ifdef __WXMSW__
#include <wx/volume.h>
#endif // __WXMSW__

using namespace std;

//(*IdInit(pnlUpdate)
const long pnlUpdate::ID_M_PLBL3 = wxNewId();
const long pnlUpdate::ID_M_PLST2 = wxNewId();
const long pnlUpdate::ID_M_PKBD1 = wxNewId();
const long pnlUpdate::ID_M_PLBL1 = wxNewId();
const long pnlUpdate::ID_M_PLBL5 = wxNewId();
const long pnlUpdate::ID_M_PEDT1 = wxNewId();
const long pnlUpdate::ID_M_PLBL6 = wxNewId();
const long pnlUpdate::ID_M_PBTN4 = wxNewId();
const long pnlUpdate::ID_PANEL1 = wxNewId();
const long pnlUpdate::ID_M_PKBD2 = wxNewId();
const long pnlUpdate::ID_M_PLBL2 = wxNewId();
const long pnlUpdate::ID_M_PLBL10 = wxNewId();
const long pnlUpdate::ID_M_PEDT2 = wxNewId();
const long pnlUpdate::ID_M_PLBL11 = wxNewId();
const long pnlUpdate::ID_M_PBTN5 = wxNewId();
const long pnlUpdate::ID_PANEL3 = wxNewId();
const long pnlUpdate::ID_M_PLST1 = wxNewId();
const long pnlUpdate::ID_M_PBTN2 = wxNewId();
const long pnlUpdate::ID_M_PBTN3 = wxNewId();
const long pnlUpdate::ID_M_PLBL7 = wxNewId();
const long pnlUpdate::ID_M_PLBL8 = wxNewId();
const long pnlUpdate::ID_M_PLBL9 = wxNewId();
const long pnlUpdate::ID_M_PLBL4 = wxNewId();
const long pnlUpdate::ID_PANEL2 = wxNewId();
const long pnlUpdate::ID_M_PLBL13 = wxNewId();
const long pnlUpdate::ID_M_PBTN6 = wxNewId();
const long pnlUpdate::ID_M_PLST3 = wxNewId();
const long pnlUpdate::ID_M_PLBL12 = wxNewId();
const long pnlUpdate::ID_PANEL4 = wxNewId();
const long pnlUpdate::ID_M_PSWP1 = wxNewId();
const long pnlUpdate::ID_M_PBTN1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlUpdate,wxPanel)
	//(*EventTable(pnlUpdate)
	//*)
END_EVENT_TABLE()

pnlUpdate::pnlUpdate(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, unsigned long n, const wxString& s)
{
	//(*Initialize(pnlUpdate)
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	SetBackgroundColour(wxColour(0,0,0));
	m_pLbl3 = new wmLabel(this, ID_M_PLBL3, _("Manage Update Settings"), wxPoint(0,5), wxSize(600,30), 0, _T("ID_M_PLBL3"));
	m_pLbl3->SetBorderState(uiRect::BORDER_NONE);
	m_pLbl3->SetForegroundColour(wxColour(255,255,255));
	m_pLbl3->SetBackgroundColour(wxColour(0,64,0));
	wxFont m_pLbl3Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	m_pLbl3->SetFont(m_pLbl3Font);
	m_plstType = new wmList(this, ID_M_PLST2, wxPoint(0,36), wxSize(600,34), wmList::STYLE_SELECT, 0, wxSize(100,30), 3, wxSize(-1,-1));
	m_plstType->SetButtonColour(wxColour(wxT("#400080")));
	m_plstType->SetSelectedButtonColour(wxColour(wxT("#FF8000")));
	m_pswpType = new wmSwitcherPanel(this, ID_M_PSWP1, wxPoint(0,70), wxSize(600,315), wmSwitcherPanel::STYLE_NOSWIPE|wmSwitcherPanel::STYLE_NOANIMATION, _T("ID_M_PSWP1"));
	m_pswpType->SetPageNameStyle(0);
	Panel1 = new wxPanel(m_pswpType, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	Panel1->SetBackgroundColour(wxColour(0,0,0));
	m_pKbd1 = new wmKeyboard(Panel1, ID_M_PKBD1, wxPoint(0,75), wxSize(600,240), 0, 0);
	m_pKbd1->SetForegroundColour(wxColour(255,255,255));
	wxFont m_pKbd1Font(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	m_pKbd1->SetFont(m_pKbd1Font);
	m_pLbl1 = new wmLabel(Panel1, ID_M_PLBL1, _("Current:"), wxPoint(5,5), wxSize(100,30), 0, _T("ID_M_PLBL1"));
	m_pLbl1->SetBorderState(uiRect::BORDER_NONE);
	m_pLbl1->SetForegroundColour(wxColour(255,255,255));
	m_pLbl1->SetBackgroundColour(wxColour(0,0,160));
	m_pLbl4 = new wmLabel(Panel1, ID_M_PLBL5, _("Set To:"), wxPoint(5,40), wxSize(100,30), 0, _T("ID_M_PLBL5"));
	m_pLbl4->SetBorderState(uiRect::BORDER_NONE);
	m_pLbl4->SetForegroundColour(wxColour(255,255,255));
	m_pLbl4->SetBackgroundColour(wxColour(0,0,160));
	m_pedtHTTP = new wmEdit(Panel1, ID_M_PEDT1, wxEmptyString, wxPoint(105,40), wxSize(350,30), 0, wxDefaultValidator, _T("ID_M_PEDT1"));
	m_pedtHTTP->SetValidation(0);
	m_pedtHTTP->SetForegroundColour(wxColour(0,0,0));
	m_pedtHTTP->SetBackgroundColour(wxColour(255,255,255));
	m_pedtHTTP->SetFocusedBackground(wxColour(wxT("#FFFF80")));
	m_pedtHTTP->SetBorderStyle(1,1);
	m_plblHTTPCurrent = new wmLabel(Panel1, ID_M_PLBL6, wxEmptyString, wxPoint(105,5), wxSize(350,30), 0, _T("ID_M_PLBL6"));
	m_plblHTTPCurrent->SetBorderState(uiRect::BORDER_NONE);
	m_plblHTTPCurrent->SetBackgroundColour(wxColour(255,255,255));
	m_pbtnSetHttp = new wmButton(Panel1, ID_M_PBTN4, _("Set"), wxPoint(470,15), wxSize(90,40), 0, wxDefaultValidator, _T("ID_M_PBTN4"));
	m_pbtnSetHttp->SetBackgroundColour(wxColour(128,64,0));
	wxFont m_pbtnSetHttpFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	m_pbtnSetHttp->SetFont(m_pbtnSetHttpFont);
	pnlShare = new wxPanel(m_pswpType, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	pnlShare->SetBackgroundColour(wxColour(0,0,0));
	m_pKbd2 = new wmKeyboard(pnlShare, ID_M_PKBD2, wxPoint(0,75), wxSize(600,240), 0, 0);
	m_pKbd2->SetForegroundColour(wxColour(255,255,255));
	wxFont m_pKbd2Font(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	m_pKbd2->SetFont(m_pKbd2Font);
	m_plblShareCurrent = new wmLabel(pnlShare, ID_M_PLBL2, _("Current:"), wxPoint(5,5), wxSize(100,30), 0, _T("ID_M_PLBL2"));
	m_plblShareCurrent->SetBorderState(uiRect::BORDER_NONE);
	m_plblShareCurrent->SetForegroundColour(wxColour(255,255,255));
	m_plblShareCurrent->SetBackgroundColour(wxColour(0,0,160));
	m_plblShareSet = new wmLabel(pnlShare, ID_M_PLBL10, _("Set To:"), wxPoint(5,40), wxSize(100,30), 0, _T("ID_M_PLBL10"));
	m_plblShareSet->SetBorderState(uiRect::BORDER_NONE);
	m_plblShareSet->SetForegroundColour(wxColour(255,255,255));
	m_plblShareSet->SetBackgroundColour(wxColour(0,0,160));
	m_pedtShare = new wmEdit(pnlShare, ID_M_PEDT2, wxEmptyString, wxPoint(105,40), wxSize(350,30), 0, wxDefaultValidator, _T("ID_M_PEDT2"));
	m_pedtShare->SetValidation(0);
	m_pedtShare->SetForegroundColour(wxColour(0,0,0));
	m_pedtShare->SetBackgroundColour(wxColour(255,255,255));
	m_pedtShare->SetFocusedBackground(wxColour(wxT("#FFFF80")));
	m_pedtShare->SetBorderStyle(1,1);
	m_pLbl8 = new wmLabel(pnlShare, ID_M_PLBL11, wxEmptyString, wxPoint(105,5), wxSize(350,30), 0, _T("ID_M_PLBL11"));
	m_pLbl8->SetBorderState(uiRect::BORDER_NONE);
	m_pLbl8->SetBackgroundColour(wxColour(255,255,255));
	m_pbtnShareSet = new wmButton(pnlShare, ID_M_PBTN5, _("Set"), wxPoint(470,15), wxSize(90,40), 0, wxDefaultValidator, _T("ID_M_PBTN5"));
	m_pbtnShareSet->SetBackgroundColour(wxColour(128,64,0));
	wxFont m_pbtnShareSetFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	m_pbtnShareSet->SetFont(m_pbtnShareSetFont);
	Panel2 = new wxPanel(m_pswpType, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	Panel2->SetBackgroundColour(wxColour(0,0,0));
	m_plstFolders = new wmList(Panel2, ID_M_PLST1, wxPoint(0,75), wxSize(600,240), 0, 1, wxSize(-1,50), 5, wxSize(5,5));
	m_plstFolders->SetBorderStyle(3);
	m_plstFolders->SetButtonColour(wxColour(wxT("#FFFFFF")));
	m_plstFolders->SetPressedButtonColour(wxColour(wxT("#FF8040")));
	m_plstFolders->SetTextButtonColour(wxColour(wxT("#000000")));
	m_pbtnUp = new wmButton(Panel2, ID_M_PBTN2, _("Up"), wxPoint(430,40), wxSize(40,30), 0, wxDefaultValidator, _T("ID_M_PBTN2"));
	m_pbtnSelect = new wmButton(Panel2, ID_M_PBTN3, _("Select"), wxPoint(480,15), wxSize(90,40), 0, wxDefaultValidator, _T("ID_M_PBTN3"));
	m_pbtnSelect->SetBackgroundColour(wxColour(128,64,0));
	m_pLbl5 = new wmLabel(Panel2, ID_M_PLBL7, _("Current:"), wxPoint(5,5), wxSize(100,30), 0, _T("ID_M_PLBL7"));
	m_pLbl5->SetBorderState(uiRect::BORDER_NONE);
	m_pLbl5->SetForegroundColour(wxColour(255,255,255));
	m_pLbl5->SetBackgroundColour(wxColour(0,0,160));
	m_pLbl6 = new wmLabel(Panel2, ID_M_PLBL8, _("Set To:"), wxPoint(5,40), wxSize(100,30), 0, _T("ID_M_PLBL8"));
	m_pLbl6->SetBorderState(uiRect::BORDER_NONE);
	m_pLbl6->SetForegroundColour(wxColour(255,255,255));
	m_pLbl6->SetBackgroundColour(wxColour(0,0,160));
	m_plblLocalCurrent = new wmLabel(Panel2, ID_M_PLBL9, wxEmptyString, wxPoint(105,5), wxSize(320,30), 0, _T("ID_M_PLBL9"));
	m_plblLocalCurrent->SetBorderState(uiRect::BORDER_NONE);
	m_plblLocalCurrent->SetBackgroundColour(wxColour(255,255,255));
	m_plblLocation = new wmLabel(Panel2, ID_M_PLBL4, wxEmptyString, wxPoint(105,40), wxSize(320,30), 0, _T("ID_M_PLBL4"));
	m_plblLocation->SetBorderState(uiRect::BORDER_NONE);
	m_plblLocation->SetForegroundColour(wxColour(0,0,0));
	m_plblLocation->SetBackgroundColour(wxColour(255,255,255));
	pnlUSB = new wxPanel(m_pswpType, ID_PANEL4, wxPoint(0,0), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	pnlUSB->SetBackgroundColour(wxColour(0,0,0));
	m_pLbl7 = new wmLabel(pnlUSB, ID_M_PLBL13, _("Connect a USB Drive and press Detect button"), wxPoint(0,0), wxSize(600,60), 0, _T("ID_M_PLBL13"));
	m_pLbl7->SetBorderState(uiRect::BORDER_NONE);
	m_pLbl7->SetForegroundColour(wxColour(255,255,255));
	m_pLbl7->SetBackgroundColour(*wxBLACK);
	wxFont m_pLbl7Font(18,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
	m_pLbl7->SetFont(m_pLbl7Font);
	m_pbtnDetect = new wmButton(pnlUSB, ID_M_PBTN6, _("Detect USB Drive"), wxPoint(200,60), wxSize(200,40), 0, wxDefaultValidator, _T("ID_M_PBTN6"));
	m_pbtnDetect->SetBackgroundColour(wxColour(0,0,255));
	wxFont m_pbtnDetectFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
	m_pbtnDetect->SetFont(m_pbtnDetectFont);
	m_plstUsb = new wmList(pnlUSB, ID_M_PLST3, wxPoint(0,200), wxSize(600,120), wmList::STYLE_SELECT, 0, wxSize(-1,40), 6, wxSize(5,5));
	m_plstUsb->SetBackgroundColour(wxColour(0,0,0));
	m_plblUSB = new wmLabel(pnlUSB, ID_M_PLBL12, wxEmptyString, wxPoint(0,100), wxSize(600,100), 0, _T("ID_M_PLBL12"));
	m_plblUSB->SetBorderState(uiRect::BORDER_NONE);
	m_plblUSB->SetForegroundColour(wxColour(0,255,0));
	m_plblUSB->SetBackgroundColour(*wxBLACK);
	wxFont m_plblUSBFont(18,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
	m_plblUSB->SetFont(m_plblUSBFont);
	m_pswpType->AddPage(Panel1, _("HTTP"), false);
	m_pswpType->AddPage(pnlShare, _("Share"), false);
	m_pswpType->AddPage(Panel2, _("Local"), false);
	m_pswpType->AddPage(pnlUSB, _("USB"), false);
	m_pbtnCheck = new wmButton(this, ID_M_PBTN1, _("Check For Updates"), wxPoint(200,390), wxSize(200,40), 0, wxDefaultValidator, _T("ID_M_PBTN1"));
	m_pbtnCheck->SetBackgroundColour(wxColour(67,167,69));
	wxFont m_pbtnCheckFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
	m_pbtnCheck->SetFont(m_pbtnCheckFont);

	Connect(ID_M_PLST2,wxEVT_LIST_SELECTED,(wxObjectEventFunction)&pnlUpdate::OnlstTypeSelected);
	Connect(ID_M_PBTN4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlUpdate::OnbtnSetHttpClick);
	Connect(ID_M_PBTN5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlUpdate::OnbtnShareSetClick);
	Connect(ID_M_PLST1,wxEVT_LIST_SELECTED,(wxObjectEventFunction)&pnlUpdate::OnlstFoldersSelected);
	Connect(ID_M_PBTN2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlUpdate::OnbtnUpClick);
	Connect(ID_M_PBTN3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlUpdate::OnbtnSelectClick);
	Connect(ID_M_PBTN6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlUpdate::OnbtnDetectClick);
	Connect(ID_M_PLST3,wxEVT_LIST_SELECTED,(wxObjectEventFunction)&pnlUpdate::OnlstUsbSelected);
	Connect(ID_M_PBTN1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlUpdate::OnbtnCheckClick);
	//*)
	m_pbtnCheck->SetColourDisabled(wxColour(120,120,120));
    m_plstFolders->SetGradient(0);
    m_plstFolders->SetTextAlign(wxALIGN_BOTTOM | wxALIGN_CENTER_HORIZONTAL);
    m_plstFolders->SetBitmapAlign(wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL);
	SetSize(size);
	SetPosition(pos);

	m_plstType->AddButton(wxT("HTTP"));
	//m_plstType->AddButton(wxT("FTP"));
    m_plstType->AddButton(wxT("Share"));
    m_plstType->AddButton(wxT("Local"));
    m_plstType->AddButton(wxT("USB"));

	m_plstType->SelectButton(Settings::Get().Read(wxT("Update"), wxT("Type"), wxT("Share")), true);

	m_plblLocation->SetTextAlign(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	m_plblLocation->GetUiRect().Pad(10,0);

    m_sLocation = Settings::Get().Read(wxT("Update"), wxT("Local"), wxEmptyString);
    m_plblLocalCurrent->SetLabel(m_sLocation);

    m_plblHTTPCurrent->SetLabel(Settings::Get().Read(wxT("Update"), wxT("HTTP"), wxEmptyString));
    m_pLbl8->SetLabel(Settings::Get().Read(wxT("Update"), wxT("Share"), wxEmptyString));


	if(m_sLocation.empty() == false)
	{
	    ShowDirectories();
	}
	else
    {
        ShowDrives();
    }

    m_timerUSB.SetOwner(this, wxNewId());
    Connect(m_timerUSB.GetId(), wxEVT_TIMER, (wxObjectEventFunction)&pnlUpdate::OnTimerUSB);
    Connect(wxEVT_SHOW, (wxObjectEventFunction)&pnlUpdate::OnShown);

}

pnlUpdate::~pnlUpdate()
{
	//(*Destroy(pnlUpdate)
	//*)
}


void pnlUpdate::OnlstTypeSelected(wxCommandEvent& event)
{
    m_pswpType->ChangeSelection(event.GetString());
    if(event.GetString() == wxT("USB") && IsShownOnScreen())
    {
        CheckUSB();
        m_timerUSB.Start(1000, true);
    }
    else
    {
        m_timerUSB.Stop();
    }

    Settings::Get().Write(wxT("Update"), wxT("Type"), event.GetString());
}
void pnlUpdate::OnlstFoldersSelected(wxCommandEvent& event)
{
    if(m_sLocation.empty() == false && m_sLocation.GetChar(m_sLocation.length()-1) != wxT('/'))
        m_sLocation << wxT("/");

    m_sLocation << event.GetString();

    ShowDirectories();
}

void pnlUpdate::ShowDirectories()
{
    m_plstFolders->Freeze();
    m_plstFolders->Clear();

    m_plblLocation->SetLabel(m_sLocation);
    wxDir dir(m_sLocation);
    if(dir.IsOpened())
	{
	    wxString sFilename;
        bool bCont = dir.GetFirst(&sFilename, wxT("*"), wxDIR_DIRS);
        while ( bCont )
        {
            m_plstFolders->AddButton(sFilename, wxBitmap(folder_xpm));
            bCont = dir.GetNext(&sFilename);
        }
	}
    m_plstFolders->Thaw();
}

void pnlUpdate::OnbtnUpClick(wxCommandEvent& event)
{
    if(m_sLocation != wxT('/') && m_sLocation.GetChar(m_sLocation.length()-2) != wxT(':'))
    {
        m_sLocation = m_sLocation.BeforeLast(wxT('/')).BeforeLast(wxT('/'));
        m_sLocation += wxT('/');
        ShowDirectories();
    }
    else
    {
        m_sLocation = wxEmptyString;
        m_plblLocation->SetLabel(wxEmptyString);
        ShowDrives();
    }

}


void pnlUpdate::ShowDrives()
{
    m_plstFolders->Freeze();
    m_plstFolders->Clear();
#ifdef __WXMSW__
    wxArrayString asVolumes(wxFSVolume::GetVolumes());

    for(int i = 0; i < asVolumes.GetCount(); i++)
    {
        wxFSVolume aVolume(asVolumes[i]);
        if(aVolume.GetKind() == wxFS_VOL_DISK || aVolume.GetKind() == wxFS_VOL_NETWORK)
        {
            asVolumes[i].Replace(wxT("\\"), wxT(""));
            m_plstFolders->AddButton(asVolumes[i], wxBitmap(aVolume.GetIcon(wxFS_VOL_ICO_LARGE)));
        }
    }
#else
    m_plstFolders->AddButton(wxT("/"));
#endif

    m_plstFolders->Thaw();


}

void pnlUpdate::OnbtnSelectClick(wxCommandEvent& event)
{
    Settings::Get().Write(wxT("Update"), wxT("Local"), m_sLocation);
    m_plblLocalCurrent->SetLabel(m_sLocation);
}

void pnlUpdate::OnbtnCheckClick(wxCommandEvent& event)
{
     #ifdef __WXDEBUG__
        #ifdef __WXMSW__
            wxString sUpdate = wxT("C:\\developer\\matt\\pam2\\pamupdatemanager\\bin\\Debug\\pamupdatemanager");
        #else
          wxString sUpdate = wxT("pamupdatemanager");
        #endif
    #else
        #ifdef __WXMSW__
            wxString sUpdate = wxT("pamupdatemanager");
        #else
        wxString Update = wxT("sudo pamupdatemanager");
        #endif // __WXMSW__
    #endif

    wxExecute(sUpdate);
}

void pnlUpdate::OnbtnSetHttpClick(wxCommandEvent& event)
{
    Settings::Get().Write(wxT("Update"), wxT("HTTP"), m_pedtHTTP->GetValue());
    m_plblHTTPCurrent->SetLabel(Settings::Get().Read(wxT("Update"), wxT("HTTP"), wxEmptyString));
}

void pnlUpdate::OnbtnShareSetClick(wxCommandEvent& event)
{
    Settings::Get().Write(wxT("Update"), wxT("Share"), m_pedtShare->GetValue());
    m_pLbl8->SetLabel(Settings::Get().Read(wxT("Update"), wxT("Share"), wxEmptyString));
}


void pnlUpdate::OnTimerUSB(wxTimerEvent& event)
{
    CheckUSB();
}

void pnlUpdate::OnbtnDetectClick(wxCommandEvent& event)
{
    CheckUSB();
}

void pnlUpdate::CheckUSB()
{
    wxLogDebug(wxT("CheckUSB"));
    m_plstUsb->Freeze();
    m_plstUsb->Clear();
    m_pbtnCheck->Enable(false);
    wxArrayString asFiles;
    wxExecute(wxT("sh -c \"lsblk -l -o name,label | grep sd \""), asFiles);
    for(size_t i = 0; i < asFiles.GetCount(); i++)
    {
        //NAME="sda1" LABEL="KINGSTON"
        wxString sDevice(asFiles[i].BeforeFirst(wxT(' ')));
        wxString sLabel(asFiles[i].AfterFirst(wxT(' ')).Trim(false));
        if(sLabel.empty() == false)
        {
            m_mUsb.insert(make_pair(sLabel, sDevice));
            m_plstUsb->AddButton(sLabel);
        }
    }
    if(m_plstUsb->GetItemCount() == 0)
    {
        m_plblUSB->SetLabel(wxT("No USB Drives Detected"));
        m_plblUSB->SetForegroundColour(*wxRED);
        m_pbtnDetect->Show();
        m_pLbl7->Show();
    }
    else if(m_plstUsb->GetItemCount() == 1)
    {
        m_plblUSB->SetLabel(wxT("USB Drive Detected"));
        m_plblUSB->SetForegroundColour(*wxGREEN);
        m_plstUsb->SelectButton(0, true);
        m_plstUsb->Hide();
        m_pbtnDetect->Hide();
        m_pLbl7->Hide();
    }
    else
    {
        m_plblUSB->SetLabel(wxString::Format(wxT("%d USB Drives Detected.\nPlease select from the list."), m_plstUsb->GetItemCount()));
        m_plblUSB->SetForegroundColour(*wxGREEN);
        m_plstUsb->Show();
        m_pbtnDetect->Hide();
        for(map<wxString, wxString>::iterator itUSB = m_mUsb.begin(); itUSB != m_mUsb.end(); ++itUSB)
        {
            if(itUSB->second == Settings::Get().Read(wxT("Update"), wxT("USB"), wxEmptyString))
            {
                m_plstUsb->SelectButton(itUSB->first, true);
                break;
            }
        }

        m_pLbl7->Hide();
    }

    m_plstUsb->Thaw();

    if(IsShownOnScreen())
    {
        m_timerUSB.Start(1000, true);
    }
}

void pnlUpdate::OnlstUsbSelected(wxCommandEvent& event)
{
    map<wxString, wxString>::iterator itDevice = m_mUsb.find(event.GetString());
    if(itDevice != m_mUsb.end())
    {
        Settings::Get().Write(wxT("Update"), wxT("USB"), itDevice->second);
    }
    m_pbtnCheck->Enable(true);
}


void pnlUpdate::OnShown(wxShowEvent& event)
{
    if(event.IsShown() == false)
    {
        m_timerUSB.Stop();
    }
    else if(Settings::Get().Read(wxT("Update"), wxT("Type"), wxT("Shared")) == wxT("USB"))
    {
        m_timerUSB.Start(1000, true);
    }
}
