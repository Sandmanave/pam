#ifndef PNLSETTINGS_H
#define PNLSETTINGS_H

//(*Headers(pnlSettings)
#include <wx/notebook.h>
#include "wmbutton.h"
#include "wmkeyboard.h"
#include "wmlabel.h"
#include "wmswitcherpanel.h"
#include <wx/panel.h>
#include "wmedit.h"
#include "wmlist.h"
//*)
#include "pnlNetworkSetup.h"
#include "pnlRTP.h"
#include "pnlSettingsPlugins.h"
#include "pnlUpdate.h"
#include "pnlSettingsProfiles.h"
#include "pnlSettingsGenerators.h"

class pnlSettings: public wxPanel
{
	public:

		pnlSettings(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~pnlSettings();

		//(*Declarations(pnlSettings)
		wmLabel* m_pLbl4;
		wmList* m_plstLatency;
		wxPanel* pnlGeneral;
		wmLabel* m_pLbl3;
		wmLabel* m_plblHostname;
		wmEdit* m_pedtPin;
		wmList* m_plstDevices;
		pnlSettingsGenerators* m_ppnlGenerators;
		wmSwitcherPanel* m_pswpSettings;
		wmButton* m_pbtnPrevious;
		wmLabel* m_plblCurrentPIN;
		wmButton* m_pbtnOutput;
		wmButton* m_pbtnCursor;
		pnlSettingsPlugins* m_ppnlPlugins;
		pnlNetworkSetup* pnlSettingsNetwork;
		wmButton* m_pbtnPin;
		wmButton* m_pbtnNext;
		wmList* m_plstPlayback;
		wmLabel* m_pLbl5;
		wmList* m_plstInput;
		wmButton* m_ptbnOptions;
		wmLabel* m_pLbl8;
		wmButton* m_pbtnHome;
		wxPanel* pnlOutput;
		pnlRTP* pnlSettingsRTP;
		wmLabel* m_plblVersion;
		wxPanel* pnlInput;
		wmButton* m_pbtnEnd;
		pnlSettingsProfiles* m_ppnlProfiles;
		wmKeyboard* m_pkbdPin;
		pnlUpdate* m_ppnlUpdate;
		//*)

		void ReloadRTP();

		void InputSessionChanged();

	protected:

		//(*Identifiers(pnlSettings)
		static const long ID_M_PLBL37;
		static const long ID_M_PLBL13;
		static const long ID_M_PLBL14;
		static const long ID_M_PLBL3;
		static const long ID_M_PLST1;
		static const long ID_M_PLST2;
		static const long ID_M_PBTN1;
		static const long ID_M_PBTN2;
		static const long ID_M_PBTN4;
		static const long ID_M_PBTN5;
		static const long ID_PANEL1;
		static const long ID_M_PLBL4;
		static const long ID_M_PBTN3;
		static const long ID_M_PLST6;
		static const long ID_M_PLST4;
		static const long ID_M_PLBL5;
		static const long ID_PANEL2;
		static const long ID_PANEL8;
		static const long ID_PANEL4;
		static const long ID_PANEL5;
		static const long ID_PANEL3;
		static const long ID_PANEL7;
		static const long ID_PANEL13;
		static const long ID_M_PBTN22;
		static const long ID_M_PBTN23;
		static const long ID_M_PBTN24;
		static const long ID_M_PEDT1;
		static const long ID_M_PKBD1;
		static const long ID_M_PLBL12;
		static const long ID_PANEL6;
		static const long ID_M_PSWP1;
		//*)

	private:

		//(*Handlers(pnlSettings)
		void OnlstDevicesSelected(wxCommandEvent& event);
		void OnlstMeters_M36Selected(wxCommandEvent& event);
		void OnlstMeters_SpeedSelected(wxCommandEvent& event);
		void OnBtnExit(wxCommandEvent& event);
		void OnbtnInputClick(wxCommandEvent& event);
		void OnbtnAddSourceClick(wxCommandEvent& event);
		void OnbtnOutputClick(wxCommandEvent& event);
		void OnlstPlaybackSelected(wxCommandEvent& event);
		void OnbtnDeleteSourceClick(wxCommandEvent& event);
		void OnbtnDeleteSourceHeld(wxCommandEvent& event);
		void OnbtnMeterShadingClick(wxCommandEvent& event);
		void OnlblLatencySelected(wxCommandEvent& event);
		void OnlstInputSelected(wxCommandEvent& event);
		void OnswpSettingsPageChanged(wxNotebookEvent& event);
		void OnbtnHomeClick(wxCommandEvent& event);
		void OnbtnPreviousClick(wxCommandEvent& event);
		void OnbtnNextClick(wxCommandEvent& event);
		void OnbtnEndClick(wxCommandEvent& event);
		void OnlstAudioSourcesSelected(wxCommandEvent& event);
		void OnlstAogFilesSelected(wxCommandEvent& event);
		void OnbtnAogHomeClick(wxCommandEvent& event);
		void OnbtnAogPrevClick(wxCommandEvent& event);
		void OnbtnAogNextClick(wxCommandEvent& event);
		void OnbtnAogEndClick(wxCommandEvent& event);
		void OnbtnMinus1Click(wxCommandEvent& event);
		void OnbtnPlus1Click(wxCommandEvent& event);
		void OnbtnPlus10Click(wxCommandEvent& event);
		void OnbtnMinus10Click(wxCommandEvent& event);
		void OnlstShapeSelected(wxCommandEvent& event);
		void Onbtn450Click(wxCommandEvent& event);
		void Onbtn900Click(wxCommandEvent& event);
		void Onbtn1000Click(wxCommandEvent& event);
		void Onbtn5000Click(wxCommandEvent& event);
		void Onbtn10000Click(wxCommandEvent& event);
		void Onbtn0dbuClick(wxCommandEvent& event);
		void OnbtnSequencesClick(wxCommandEvent& event);
		void OnlstColourSelected(wxCommandEvent& event);
		void OnbtnNoise0dBuClick(wxCommandEvent& event);
		void OnbtnCursorClick(wxCommandEvent& event);
		void OnbtnOptionsClick(wxCommandEvent& event);
		void OnlstOutputLeftSelected(wxCommandEvent& event);
		void OnlstOutputRightSelected(wxCommandEvent& event);
		void OnbtnPinClick(wxCommandEvent& event);
		void OnedtPinTextEnter(wxCommandEvent& event);
		//*)

        void RefreshInputs();
		void ShowSoundcardInputs();

		void ShowRTPDefined();

        void ShowSoundcardOutputs();


        void ShowPagingButtons();


        void PopulateChannelList(wmList* pList, int nSelected);


		DECLARE_EVENT_TABLE()
};

#endif

