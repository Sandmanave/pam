#include "pnlUpdate.h"

//(*InternalHeaders(pnlUpdate)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include "dlgUpdate.h"
#include "settings.h"
#include <wx/dir.h>
#include "folder.xpm"
#include "updatemanager.h"



#ifdef __WXMSW__
#include <wx/volume.h>
#endif // __WXMSW__


//(*IdInit(pnlUpdate)
const long pnlUpdate::ID_M_PLBL3 = wxNewId();
const long pnlUpdate::ID_M_PLST2 = wxNewId();
const long pnlUpdate::ID_M_PKBD1 = wxNewId();
const long pnlUpdate::ID_M_PLBL1 = wxNewId();
const long pnlUpdate::ID_M_PEDT1 = wxNewId();
const long pnlUpdate::ID_PANEL1 = wxNewId();
const long pnlUpdate::ID_M_PKBD2 = wxNewId();
const long pnlUpdate::ID_M_PLBL2 = wxNewId();
const long pnlUpdate::ID_M_PEDT2 = wxNewId();
const long pnlUpdate::ID_PANEL3 = wxNewId();
const long pnlUpdate::ID_M_PLST1 = wxNewId();
const long pnlUpdate::ID_M_PBTN2 = wxNewId();
const long pnlUpdate::ID_M_PBTN3 = wxNewId();
const long pnlUpdate::ID_M_PLBL4 = wxNewId();
const long pnlUpdate::ID_PANEL2 = wxNewId();
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
	m_pKbd1 = new wmKeyboard(Panel1, ID_M_PKBD1, wxPoint(0,60), wxSize(600,240), 0, 0);
	m_pKbd1->SetForegroundColour(wxColour(255,255,255));
	wxFont m_pKbd1Font(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	m_pKbd1->SetFont(m_pKbd1Font);
	m_pLbl1 = new wmLabel(Panel1, ID_M_PLBL1, _("HTTPS://"), wxPoint(5,5), wxSize(100,40), 0, _T("ID_M_PLBL1"));
	m_pLbl1->SetBorderState(uiRect::BORDER_NONE);
	m_pLbl1->SetForegroundColour(wxColour(255,255,255));
	m_pLbl1->SetBackgroundColour(wxColour(0,0,160));
	m_pEdt1 = new wmEdit(Panel1, ID_M_PEDT1, wxEmptyString, wxPoint(105,5), wxSize(460,40), 0, wxDefaultValidator, _T("ID_M_PEDT1"));
	m_pEdt1->SetValidation(0);
	m_pEdt1->SetForegroundColour(wxColour(0,0,0));
	m_pEdt1->SetBackgroundColour(wxColour(255,255,255));
	m_pEdt1->SetBorderStyle(1,1);
	Panel3 = new wxPanel(m_pswpType, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	Panel3->SetBackgroundColour(wxColour(0,0,0));
	m_pKbd2 = new wmKeyboard(Panel3, ID_M_PKBD2, wxPoint(0,60), wxSize(600,240), 0, 0);
	m_pKbd2->SetForegroundColour(wxColour(255,255,255));
	wxFont m_pKbd2Font(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	m_pKbd2->SetFont(m_pKbd2Font);
	m_pLbl2 = new wmLabel(Panel3, ID_M_PLBL2, _("FTP://"), wxPoint(5,5), wxSize(100,40), 0, _T("ID_M_PLBL2"));
	m_pLbl2->SetBorderState(uiRect::BORDER_NONE);
	m_pLbl2->SetForegroundColour(wxColour(255,255,255));
	m_pLbl2->SetBackgroundColour(wxColour(0,0,160));
	m_pEdt2 = new wmEdit(Panel3, ID_M_PEDT2, wxEmptyString, wxPoint(105,5), wxSize(460,40), 0, wxDefaultValidator, _T("ID_M_PEDT2"));
	m_pEdt2->SetValidation(0);
	m_pEdt2->SetForegroundColour(wxColour(0,0,0));
	m_pEdt2->SetBackgroundColour(wxColour(255,255,255));
	m_pEdt2->SetBorderStyle(1,1);
	Panel2 = new wxPanel(m_pswpType, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	Panel2->SetBackgroundColour(wxColour(0,0,0));
	m_plstFolders = new wmList(Panel2, ID_M_PLST1, wxPoint(0,45), wxSize(600,280), 0, 1, wxSize(-1,50), 5, wxSize(5,5));
	m_plstFolders->SetBorderStyle(3);
	m_plstFolders->SetButtonColour(wxColour(wxT("#FFFFFF")));
	m_plstFolders->SetPressedButtonColour(wxColour(wxT("#FF8040")));
	m_plstFolders->SetTextButtonColour(wxColour(wxT("#000000")));
	m_pbtnUp = new wmButton(Panel2, ID_M_PBTN2, _("Up"), wxPoint(400,2), wxSize(80,40), 0, wxDefaultValidator, _T("ID_M_PBTN2"));
	m_pbtnSelect = new wmButton(Panel2, ID_M_PBTN3, _("Select"), wxPoint(500,2), wxSize(90,40), 0, wxDefaultValidator, _T("ID_M_PBTN3"));
	m_pbtnSelect->SetBackgroundColour(wxColour(128,64,0));
	m_plblLocation = new wmLabel(Panel2, ID_M_PLBL4, wxEmptyString, wxPoint(0,2), wxSize(400,40), 0, _T("ID_M_PLBL4"));
	m_plblLocation->SetBorderState(uiRect::BORDER_NONE);
	m_plblLocation->SetForegroundColour(wxColour(0,0,0));
	m_plblLocation->SetBackgroundColour(wxColour(255,255,255));
	m_pswpType->AddPage(Panel1, _("HTTP"), false);
	m_pswpType->AddPage(Panel3, _("FTP"), false);
	m_pswpType->AddPage(Panel2, _("Share"), false);
	m_pbtnCheck = new wmButton(this, ID_M_PBTN1, _("Check For Updates"), wxPoint(200,390), wxSize(200,40), 0, wxDefaultValidator, _T("ID_M_PBTN1"));
	m_pbtnCheck->SetBackgroundColour(wxColour(67,167,69));
	wxFont m_pbtnCheckFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
	m_pbtnCheck->SetFont(m_pbtnCheckFont);

	Connect(ID_M_PLST2,wxEVT_LIST_SELECTED,(wxObjectEventFunction)&pnlUpdate::OnlstTypeSelected);
	Connect(ID_M_PLST1,wxEVT_LIST_SELECTED,(wxObjectEventFunction)&pnlUpdate::OnlstFoldersSelected);
	Connect(ID_M_PBTN2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlUpdate::OnbtnUpClick);
	Connect(ID_M_PBTN3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlUpdate::OnbtnSelectClick);
	Connect(ID_M_PBTN1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlUpdate::OnbtnCheckClick);
	//*)
    m_plstFolders->SetGradient(0);
    m_plstFolders->SetTextAlign(wxALIGN_BOTTOM | wxALIGN_CENTER_HORIZONTAL);
    m_plstFolders->SetBitmapAlign(wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL);
	SetSize(size);
	SetPosition(pos);

	m_plstType->AddButton(wxT("HTTP"));
	m_plstType->AddButton(wxT("FTP"));
	m_plstType->AddButton(wxT("Share"));


	m_plstType->SelectButton(Settings::Get().Read(wxT("Update"), wxT("Type"), wxT("Share")), true);

	m_plblLocation->SetTextAlign(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	m_plblLocation->GetUiRect().Pad(10,0);
    m_sLocation = Settings::Get().Read(wxT("Update"), wxT("Share"), wxEmptyString);
	if(m_sLocation.empty() == false)
	{
	    ShowDirectories();
	}
	else
    {
        ShowDrives();
    }

}

pnlUpdate::~pnlUpdate()
{
	//(*Destroy(pnlUpdate)
	//*)
}


void pnlUpdate::OnlstTypeSelected(wxCommandEvent& event)
{
    m_pswpType->ChangeSelection(event.GetString());

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
    Settings::Get().Write(wxT("Update"), wxT("Share"), m_sLocation);
}

void pnlUpdate::OnbtnCheckClick(wxCommandEvent& event)
{
    dlgUpdate aDlg(this);
    aDlg.ShowModal();
}
