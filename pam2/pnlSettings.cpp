#include "pnlSettings.h"
#include "portaudio.h"
#include <wx/app.h>
#include <wx/log.h>
#include <wx/utils.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/msgdlg.h>
#include <wx/stdpaths.h>
#include "settings.h"
//#include "meter.h"
#include "version.h"
#include "dlgSequence.h"
#include "iomanager.h"
#include "dlgmask.h"
//(*InternalHeaders(pnlSettings)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)
#include <iostream>

#include "images/end_hz.xpm"
#include "images/end_hz_press.xpm"
#include "images/home_hz_press.xpm"
#include "images/home_hz.xpm"
#include "images/pagedown.xpm"
#include "images/pagedown_press.xpm"
#include "images/pageup.xpm"
#include "images/pageup_press.xpm"
#include "soundcardmanager.h"
#include "dlgAoIP.h"
#include "settingevent.h"
#include "aoipsourcemanager.h"


using namespace std;

//(*IdInit(pnlSettings)
const long pnlSettings::ID_M_PLBL37 = wxNewId();
const long pnlSettings::ID_M_PLBL13 = wxNewId();
const long pnlSettings::ID_M_PLBL14 = wxNewId();
const long pnlSettings::ID_M_PLBL3 = wxNewId();
const long pnlSettings::ID_M_PLST1 = wxNewId();
const long pnlSettings::ID_M_PBTN1 = wxNewId();
const long pnlSettings::ID_M_PBTN2 = wxNewId();
const long pnlSettings::ID_M_PBTN4 = wxNewId();
const long pnlSettings::ID_M_PBTN5 = wxNewId();
const long pnlSettings::ID_M_PLBL1 = wxNewId();
const long pnlSettings::ID_M_PSLIDER1 = wxNewId();
const long pnlSettings::ID_PANEL10 = wxNewId();
const long pnlSettings::ID_PANEL11 = wxNewId();
const long pnlSettings::ID_M_PSWP2 = wxNewId();
const long pnlSettings::ID_M_PLST2 = wxNewId();
const long pnlSettings::ID_M_PBTN7 = wxNewId();
const long pnlSettings::ID_M_PLBL2 = wxNewId();
const long pnlSettings::ID_PANEL1 = wxNewId();
const long pnlSettings::ID_PANEL2 = wxNewId();
const long pnlSettings::ID_PANEL8 = wxNewId();
const long pnlSettings::ID_PANEL5 = wxNewId();
const long pnlSettings::ID_PANEL3 = wxNewId();
const long pnlSettings::ID_PANEL7 = wxNewId();
const long pnlSettings::ID_PANEL13 = wxNewId();
const long pnlSettings::ID_PANEL4 = wxNewId();
const long pnlSettings::ID_PANEL9 = wxNewId();
const long pnlSettings::ID_M_PBTN22 = wxNewId();
const long pnlSettings::ID_M_PBTN23 = wxNewId();
const long pnlSettings::ID_M_PBTN24 = wxNewId();
const long pnlSettings::ID_M_PEDT1 = wxNewId();
const long pnlSettings::ID_M_PKBD1 = wxNewId();
const long pnlSettings::ID_M_PLBL12 = wxNewId();
const long pnlSettings::ID_PANEL6 = wxNewId();
const long pnlSettings::ID_M_PSWP1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlSettings,wxPanel)
	//(*EventTable(pnlSettings)
	//*)
END_EVENT_TABLE()


pnlSettings::pnlSettings(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(pnlSettings)
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
    SetBackgroundColour(wxColour(0,0,0));
    m_plblHostname = new wmLabel(this, ID_M_PLBL37, _("Settings"), wxPoint(0,0), wxSize(200,40), 0, _T("ID_M_PLBL37"));
    m_plblHostname->SetBorderState(uiRect::BORDER_NONE);
    m_plblHostname->GetUiRect().SetGradient(0);
    m_plblHostname->SetForegroundColour(wxColour(255,255,255));
    m_plblHostname->SetBackgroundColour(wxColour(61,146,146));
    wxFont m_plblHostnameFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    m_plblHostname->SetFont(m_plblHostnameFont);
    m_pLbl8 = new wmLabel(this, ID_M_PLBL13, _("Settings"), wxPoint(200,0), wxSize(200,40), 0, _T("ID_M_PLBL13"));
    m_pLbl8->SetBorderState(uiRect::BORDER_NONE);
    m_pLbl8->GetUiRect().SetGradient(0);
    m_pLbl8->SetForegroundColour(wxColour(255,255,255));
    m_pLbl8->SetBackgroundColour(wxColour(61,146,146));
    wxFont m_pLbl8Font(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    m_pLbl8->SetFont(m_pLbl8Font);
    m_plblVersion = new wmLabel(this, ID_M_PLBL14, wxEmptyString, wxPoint(400,0), wxSize(200,40), 0, _T("ID_M_PLBL14"));
    m_plblVersion->SetBorderState(uiRect::BORDER_NONE);
    m_plblVersion->GetUiRect().SetGradient(0);
    m_plblVersion->SetForegroundColour(wxColour(255,255,255));
    m_plblVersion->SetBackgroundColour(wxColour(61,146,146));
    wxFont m_plblVersionFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    m_plblVersion->SetFont(m_plblVersionFont);
    m_pswpSettings = new wmSwitcherPanel(this, ID_M_PSWP1, wxPoint(0,40), wxSize(600,440), wmSwitcherPanel::STYLE_NOSWIPE|wmSwitcherPanel::STYLE_NOANIMATION, _T("ID_M_PSWP1"));
    m_pswpSettings->SetPageNameStyle(0);
    pnlInput = new wxPanel(m_pswpSettings, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    pnlInput->SetBackgroundColour(wxColour(0,0,0));
    m_pLbl3 = new wmLabel(pnlInput, ID_M_PLBL3, _("Audio Monitoring Source"), wxPoint(0,5), wxSize(600,30), 0, _T("ID_M_PLBL3"));
    m_pLbl3->SetBorderState(uiRect::BORDER_NONE);
    m_pLbl3->GetUiRect().SetGradient(0);
    m_pLbl3->SetForegroundColour(wxColour(255,255,255));
    m_pLbl3->SetBackgroundColour(wxColour(0,64,0));
    wxFont m_pLbl3Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    m_pLbl3->SetFont(m_pLbl3Font);
    m_pswpInput = new wmSwitcherPanel(pnlInput, ID_M_PSWP2, wxPoint(0,70), wxSize(600,410), wmSwitcherPanel::STYLE_NOSWIPE|wmSwitcherPanel::STYLE_NOANIMATION, _T("ID_M_PSWP2"));
    m_pswpInput->SetPageNameStyle(0);
    Panel1 = new wxPanel(m_pswpInput, ID_PANEL10, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL10"));
    Panel1->SetBackgroundColour(wxColour(0,0,0));
    m_plstDevices = new wmList(Panel1, ID_M_PLST1, wxPoint(0,0), wxSize(600,280), wmList::STYLE_SELECT, 2, wxSize(-1,40), 3, wxSize(5,5));
    m_plstDevices->SetBackgroundColour(wxColour(0,0,0));
    m_plstDevices->SetSelectedButtonColour(wxColour(wxT("#008000")));
    m_plstDevices->SetDisabledColour(wxColour(wxT("#808080")));
    m_pbtnHome = new wmButton(Panel1, ID_M_PBTN1, wxEmptyString, wxPoint(70,282), wxSize(100,40), 0, wxDefaultValidator, _T("ID_M_PBTN1"));
    m_pbtnHome->SetColourDisabled(wxColour(wxT("#808080")));
    m_pbtnPrevious = new wmButton(Panel1, ID_M_PBTN2, wxEmptyString, wxPoint(190,282), wxSize(100,40), 0, wxDefaultValidator, _T("ID_M_PBTN2"));
    m_pbtnPrevious->SetColourDisabled(wxColour(wxT("#808080")));
    m_pbtnNext = new wmButton(Panel1, ID_M_PBTN4, wxEmptyString, wxPoint(310,282), wxSize(100,40), 0, wxDefaultValidator, _T("ID_M_PBTN4"));
    m_pbtnNext->SetColourDisabled(wxColour(wxT("#808080")));
    m_pbtnEnd = new wmButton(Panel1, ID_M_PBTN5, wxEmptyString, wxPoint(430,282), wxSize(100,40), 0, wxDefaultValidator, _T("ID_M_PBTN5"));
    m_pbtnEnd->SetColourDisabled(wxColour(wxT("#808080")));
    m_pLbl1 = new wmLabel(Panel1, ID_M_PLBL1, _("Gain"), wxPoint(10,330), wxSize(70,30), 0, _T("ID_M_PLBL1"));
    m_pLbl1->SetBorderState(uiRect::BORDER_NONE);
    m_pLbl1->GetUiRect().SetGradient(0);
    m_pLbl1->SetForegroundColour(wxColour(255,255,255));
    m_pLbl1->SetBackgroundColour(wxColour(0,64,0));
    wxFont m_pLbl1Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    m_pLbl1->SetFont(m_pLbl1Font);
    m_plsliderInputGain = new wmSlider(Panel1, ID_M_PSLIDER1, _("Slider"), wxPoint(80,330), wxSize(400,30));
    m_plsliderInputGain->Init(0,10000,5000);
    m_ppnlAoIPManual = new pnlAoipManual(m_pswpInput, ID_PANEL11, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL11"));
    m_pswpInput->AddPage(Panel1, _("Auto"), false);
    m_pswpInput->AddPage(m_ppnlAoIPManual, _("Manual"), false);
    m_plstInput = new wmList(pnlInput, ID_M_PLST2, wxPoint(0,36), wxSize(500,34), wmList::STYLE_SELECT, 0, wxSize(100,30), 3, wxSize(-1,-1));
    m_plstInput->SetButtonColour(wxColour(wxT("#400080")));
    m_plstInput->SetSelectedButtonColour(wxColour(wxT("#FF8000")));
    m_pbtnManage = new wmButton(pnlInput, ID_M_PBTN7, _("Manage"), wxPoint(510,38), wxSize(80,30), 0, wxDefaultValidator, _T("ID_M_PBTN7"));
    m_pbtnManage->SetColourDisabled(wxColour(wxT("#808080")));
    m_plblInputGain = new wmLabel(Panel1, ID_M_PLBL2, wxEmptyString, wxPoint(480,400), wxSize(70,30), 0, _T("ID_M_PLBL2"));
    m_plblInputGain->SetBorderState(uiRect::BORDER_NONE);
    m_plblInputGain->GetUiRect().SetGradient(0);
    m_plblInputGain->SetForegroundColour(wxColour(0,0,0));
    m_plblInputGain->SetBackgroundColour(wxColour(255,255,255));
    wxFont m_plblInputGainFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    m_plblInputGain->SetFont(m_plblInputGainFont);
    m_ppnlOutput = new pnlSettingsOutput(m_pswpSettings, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    m_ppnlGenerators = new pnlSettingsGenerators(m_pswpSettings, ID_PANEL8, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL8"));
    pnlSettingsNetwork = new pnlNetworkSetup(m_pswpSettings, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    m_ppnlPlugins = new pnlSettingsPlugins(m_pswpSettings, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    m_ppnlUpdate = new pnlUpdate(m_pswpSettings, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
    m_ppnlProfiles = new pnlSettingsProfiles(m_pswpSettings, ID_PANEL13, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL13"));
    m_ppnlNmos = new pnlSettingsNmos(m_pswpSettings, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    m_ppnlTime = new pnlSettingsTime(m_pswpSettings, ID_PANEL9, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL9"));
    pnlGeneral = new wxPanel(m_pswpSettings, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL6"));
    pnlGeneral->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    m_pbtnCursor = new wmButton(pnlGeneral, ID_M_PBTN22, _("Cursor"), wxPoint(10,10), wxSize(200,40), wmButton::STYLE_SELECT, wxDefaultValidator, _T("ID_M_PBTN22"));
    m_ptbnOptions = new wmButton(pnlGeneral, ID_M_PBTN23, _("View"), wxPoint(10,60), wxSize(200,40), wmButton::STYLE_SELECT, wxDefaultValidator, _T("ID_M_PBTN23"));
    m_pbtnPin = new wmButton(pnlGeneral, ID_M_PBTN24, _("PIN"), wxPoint(10,110), wxSize(200,40), wmButton::STYLE_SELECT, wxDefaultValidator, _T("ID_M_PBTN24"));
    m_pedtPin = new wmEdit(pnlGeneral, ID_M_PEDT1, wxEmptyString, wxPoint(40,200), wxSize(250,25), 0, wxDefaultValidator, _T("ID_M_PEDT1"));
    m_pedtPin->SetMaxLength(8);
    m_pedtPin->SetValidation(4);
    m_pedtPin->Hide();
    m_pedtPin->SetBorderStyle(1,1);
    m_pkbdPin = new wmKeyboard(pnlGeneral, ID_M_PKBD1, wxPoint(10,230), wxSize(360,204), 5, 0);
    m_pkbdPin->Hide();
    m_pkbdPin->SetForegroundColour(wxColour(255,255,255));
    wxFont m_pkbdPinFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    m_pkbdPin->SetFont(m_pkbdPinFont);
    m_plblCurrentPIN = new wmLabel(pnlGeneral, ID_M_PLBL12, _("Current PIN: "), wxPoint(40,170), wxSize(250,-1), 0, _T("ID_M_PLBL12"));
    m_plblCurrentPIN->SetBorderState(uiRect::BORDER_NONE);
    m_plblCurrentPIN->GetUiRect().SetGradient(0);
    m_plblCurrentPIN->Hide();
    m_plblCurrentPIN->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
    m_pswpSettings->AddPage(pnlInput, _("Input Device"), false);
    m_pswpSettings->AddPage(m_ppnlOutput, _("Output Device"), false);
    m_pswpSettings->AddPage(m_ppnlGenerators, _("Output Source"), false);
    m_pswpSettings->AddPage(pnlSettingsNetwork, _("Network"), false);
    m_pswpSettings->AddPage(m_ppnlPlugins, _("Plugins"), false);
    m_pswpSettings->AddPage(m_ppnlUpdate, _("Update"), false);
    m_pswpSettings->AddPage(m_ppnlProfiles, _("Profiles"), false);
    m_pswpSettings->AddPage(m_ppnlNmos, _("NMOS"), false);
    m_pswpSettings->AddPage(m_ppnlTime, _("Time"), false);
    m_pswpSettings->AddPage(pnlGeneral, _("General"), false);

    Connect(ID_M_PLST1,wxEVT_LIST_SELECTED,(wxObjectEventFunction)&pnlSettings::OnlstDevicesSelected);
    Connect(ID_M_PLST1,wxEVT_LIST_PAGED,(wxObjectEventFunction)&pnlSettings::OnlstDevicesPaged);
    Connect(ID_M_PBTN1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSettings::OnbtnHomeClick);
    Connect(ID_M_PBTN2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSettings::OnbtnPreviousClick);
    Connect(ID_M_PBTN4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSettings::OnbtnNextClick);
    Connect(ID_M_PBTN5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSettings::OnbtnEndClick);
    Connect(ID_M_PSLIDER1,wxEVT_SLIDER_MOVE,(wxObjectEventFunction)&pnlSettings::OnlsliderInputGainMove);
    Connect(ID_M_PLST2,wxEVT_LIST_SELECTED,(wxObjectEventFunction)&pnlSettings::OnlstInputSelected);
    Connect(ID_M_PBTN7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSettings::OnbtnManageClick);
    Connect(ID_M_PBTN22,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSettings::OnbtnCursorClick);
    Connect(ID_M_PBTN23,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSettings::OnbtnOptionsClick);
    Connect(ID_M_PBTN24,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSettings::OnbtnPinClick);
    Connect(ID_M_PEDT1,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&pnlSettings::OnedtPinTextEnter);
    //*)



    m_pbtnCursor->SetToggle(true, wxT("Hide"), wxT("Show"), 40);
    m_ptbnOptions->SetToggle(true, wxT("Screens"), wxT("Options"), 40);
    m_pbtnPin->SetToggle(true, wxT("Off"), wxT("On"), 40);
    m_plblCurrentPIN->SetTextAlign(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);


    m_pbtnEnd->SetBitmapLabel(wxBitmap(end_hz_xpm));
    m_pbtnEnd->SetBitmapSelected(wxBitmap(end_hz_press_xpm));
    m_pbtnHome->SetBitmapLabel(wxBitmap(home_hz_xpm));
    m_pbtnHome->SetBitmapSelected(wxBitmap(home_hz_press_xpm));
    m_pbtnPrevious->SetBitmapLabel(wxBitmap(pageup_xpm));
    m_pbtnPrevious->SetBitmapSelected(wxBitmap(pageup_press_xpm));
    m_pbtnNext->SetBitmapLabel(wxBitmap(pagedown_xpm));
    m_pbtnNext->SetBitmapSelected(wxBitmap(pagedown_press_xpm));



    m_pswpSettings->Connect(wxID_ANY, wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, (wxObjectEventFunction)&pnlSettings::OnswpSettingsPageChanged, NULL, this);
    SetSize(size);
    SetPosition(pos);



    m_plstInput->Freeze();
    m_plstInput->AddButton(wxT("Disabled"));
    m_plstInput->AddButton(wxT("Soundcard"));
    m_plstInput->AddButton(wxT("AoIP"));
    m_plstInput->AddButton(wxT("AoIP Manual"));

    m_plstInput->Thaw();


    UpdateDisplayedSettings();


    ShowRTPDefined();

    m_plblVersion->SetLabel(wxString::Format(wxT("%ld.%ld.%ld.%ld"), AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::REVISION));
    m_plblHostname->SetLabel(wxGetHostName());





    Connect(wxID_ANY, wxEVT_SETTING_CHANGED, (wxObjectEventFunction)&pnlSettings::OnSettingChanged);

}

pnlSettings::~pnlSettings()
{
	//(*Destroy(pnlSettings)
	//*)
}


void pnlSettings::UpdateDisplayedSettings()
{
    m_pbtnCursor->ToggleSelection((Settings::Get().Read(wxT("General"), wxT("Cursor"), 1) == 1), false);
    m_ptbnOptions->ToggleSelection((Settings::Get().Read(wxT("General"), wxT("ShowOptions"), 1) == 1), false);
    m_pbtnPin->ToggleSelection((Settings::Get().Read(wxT("General"), wxT("Pin"), 0)==1), false);

    m_plstInput->SelectButton(Settings::Get().Read(wxT("Input"), wxT("Type"), wxT("Soundcard")), true);

    double dGain = ConvertRatioToGain(Settings::Get().Read("Input", "Ratio_00", 1.0));
    m_plblInputGain->SetLabel(wxString::Format("%.2f dB", dGain));
    m_plsliderInputGain->SetSliderPosition(dGain*500+5000, false);

}

void pnlSettings::OnSettingChanged(SettingEvent& event)
{

}

void pnlSettings::OnlstDevicesSelected(wxCommandEvent& event)
{
    wxString sDevice(Settings::Get().Read(wxT("Input"), wxT("Type"), wxT("Soundcard")));
    if(sDevice == wxT("Soundcard"))
    {
        Settings::Get().Write(wxT("Input"), wxT("Device"), (int)event.GetClientData());

    }
    else if(sDevice == wxT("AoIP"))
    {
        Settings::Get().Write(wxT("Input"), wxT("AoIP"), (int)event.GetClientData());
    }
}

void pnlSettings::OnBtnExit(wxCommandEvent& event)
{
    wxTheApp->GetTopWindow()->Close();
}

void pnlSettings::OnbtnOutputClick(wxCommandEvent& event)
{
}



void pnlSettings::ShowSoundcardInputs()
{
    m_plstDevices->Freeze();
    m_plstDevices->Clear();

    int nDevices =  SoundcardManager::Get().GetNumberOfDevices();

    for(int i = 0; i < nDevices; i++)
    {
        const PaDeviceInfo* pInfo = SoundcardManager::Get().GetDeviceInfo(i);
        if(pInfo && pInfo->maxInputChannels > 0)
        {
            short nEnabled = wmList::wmENABLED;
            #ifdef __WXGTK__

            if((Settings::Get().Read(wxT("Output"), wxT("Destination"),wxT("Disabled"))!=wxT("Disabled")) && Settings::Get().Read(wxT("Output"), wxT("Device"), 0) == i)
            {
                nEnabled = wmList::wmDISABLED;
            }
            #endif // __WXGTK__

            m_plstDevices->AddButton(wxString::Format(wxT("[%d] %s [%d]"),i, wxString::FromUTF8(pInfo->name).c_str(), pInfo->maxInputChannels), wxNullBitmap, (void*)i, nEnabled);
        }
    }

    m_plstDevices->Thaw();

    ShowPagingButtons();

    int nInput = Settings::Get().Read(wxT("Input"), wxT("Device"), 0);
    int nDevice = m_plstDevices->FindButton(reinterpret_cast<void*>(nInput));
    if(nDevice == wmList::NOT_FOUND)
    {
        nDevice = 0;
    }
    m_plstDevices->SelectButton(nDevice);

}



void pnlSettings::ShowRTPDefined()
{
    m_plstDevices->Freeze();
    m_plstDevices->Clear();

    for(auto itSource = AoipSourceManager::Get().GetSourceBegin(); itSource != AoipSourceManager::Get().GetSourceEnd(); ++itSource)
    {
        m_plstDevices->AddButton(itSource->second.sName, wxNullBitmap, (void*)itSource->first);
    }
    m_plstDevices->Thaw();

    ShowPagingButtons();

    int nDevice = m_plstDevices->FindButton(reinterpret_cast<void*>(Settings::Get().Read(wxT("Input"), wxT("AoIP"), 0)));
    if(nDevice == wmList::NOT_FOUND)
    {
        nDevice = 0;
    }
    m_plstDevices->SelectButton(nDevice);

}


void pnlSettings::ShowPagingButtons()
{
    m_pbtnEnd->Show(m_plstDevices->GetPageCount() > 1 && m_plstDevices->GetCurrentPageNumber() < m_plstDevices->GetPageCount());
    m_pbtnHome->Show(m_plstDevices->GetPageCount() > 1 && m_plstDevices->GetCurrentPageNumber() > 1);
    m_pbtnPrevious->Show(m_plstDevices->GetPageCount() > 1 && m_plstDevices->GetCurrentPageNumber() > 1);
    m_pbtnNext->Show(m_plstDevices->GetPageCount() > 1 && m_plstDevices->GetCurrentPageNumber() < m_plstDevices->GetPageCount());
}


void pnlSettings::ReloadRTP()
{
    ShowRTPDefined();

}


void pnlSettings::OnlstInputSelected(wxCommandEvent& event)
{
    Settings::Get().Write(wxT("Input"), wxT("Type"),event.GetString());
    RefreshInputs();

}

void pnlSettings::RefreshInputs()
{
    wxString sType = Settings::Get().Read(wxT("Input"), wxT("Type"), wxEmptyString);
    if(sType == wxT("Soundcard"))
    {
        m_pswpInput->ChangeSelection(0);
        m_pbtnManage->Hide();
        ShowSoundcardInputs();
    }
    else if(sType == wxT("AoIP"))
    {
        m_pswpInput->ChangeSelection(0);
        m_pbtnManage->Show();
        ShowRTPDefined();
    }
    else if(sType == "AoIP Manual")
    {
        m_pswpInput->ChangeSelection(1);

    }
    else if(sType == wxT("Disabled"))
    {
        m_pbtnManage->Hide();
        m_plstDevices->Freeze();
        m_plstDevices->Clear();
        m_plstDevices->Thaw();
        ShowPagingButtons();
    }

}

void pnlSettings::OnswpSettingsPageChanged(wxNotebookEvent& event)
{
    if(m_pswpSettings->GetPageText(m_pswpSettings->GetSelection()) == wxT("Audio Input"))
    {
       RefreshInputs();
    }
    else if(m_pswpSettings->GetPageText(m_pswpSettings->GetSelection()) == wxT("Audio Output"))
    {
        m_ppnlOutput->ShowSoundcardOutputs();
    }
}

void pnlSettings::OnbtnHomeClick(wxCommandEvent& event)
{
    m_plstDevices->ShowFirstPage(false,false);

}

void pnlSettings::OnbtnPreviousClick(wxCommandEvent& event)
{
    m_plstDevices->ShowPreviousPage(false, false);

}

void pnlSettings::OnbtnNextClick(wxCommandEvent& event)
{
    m_plstDevices->ShowNextPage(false, false);

}

void pnlSettings::OnbtnEndClick(wxCommandEvent& event)
{
    m_plstDevices->ShowLastPage(false, false);

}


void pnlSettings::OnbtnPinClick(wxCommandEvent& event)
{
    Settings::Get().Write(wxT("General"), wxT("Pin"), event.IsChecked());
    m_pedtPin->Show(event.IsChecked());
    m_pkbdPin->Show(event.IsChecked());
    m_plblCurrentPIN->Show(event.IsChecked());
    if(event.IsChecked())
    {
        m_plblCurrentPIN->SetLabel(wxString::Format(wxT("Current PIN: %s"), Settings::Get().Read(wxT("General"), wxT("Pin_Value"), wxEmptyString).c_str()));
        m_pedtPin->SetValue(wxEmptyString);
        m_pedtPin->SetFocus();
    }
}

void pnlSettings::OnedtPinTextEnter(wxCommandEvent& event)
{
    Settings::Get().Write(wxT("General"), wxT("Pin_Value"), m_pedtPin->GetValue());
    m_plblCurrentPIN->SetLabel(wxString::Format(wxT("Current PIN: %s"), Settings::Get().Read(wxT("General"), wxT("Pin_Value"), wxEmptyString).c_str()));
}


void pnlSettings::InputSessionChanged()
{
    m_ppnlGenerators->InputSessionChanged();
}


void pnlSettings::OnbtnCursorClick(wxCommandEvent& event)
{
    Settings::Get().Write(wxT("General"), wxT("Cursor"), event.IsChecked());
}

void pnlSettings::OnbtnOptionsClick(wxCommandEvent& event)
{
    Settings::Get().Write(wxT("General"), wxT("ShowOptions"), event.IsChecked());
}



void pnlSettings::OnbtnManageClick(wxCommandEvent& event)
{
    dlgAoIP aDlg(this);
    aDlg.ShowModal();
    ReloadRTP();
}

void pnlSettings::OnlstDevicesPaged(wxCommandEvent& event)
{
    ShowPagingButtons();
}




void pnlSettings::OnlsliderInputGainMove(wxCommandEvent& event)
{

    double dGain = (m_plsliderInputGain->GetPosition()-5000)/500.0;

    m_plblInputGain->SetLabel(wxString::Format("%.2f dB", dGain));

    double dRatio = ConvertGainToRatio(dGain);
    for(unsigned int i = 0; i < 8; i++)
    {
        Settings::Get().Write("Input", wxString::Format("Ratio_%02d", i), dRatio);
    }
}


double pnlSettings::ConvertGainToRatio(double dGain)
{
    return pow(10.0, dGain/20.0);
}

double pnlSettings::ConvertRatioToGain(double dRatio)
{
    return 20*log10(dRatio);
}
