#ifndef PNLOPTIONS_H
#define PNLOPTIONS_H

//(*Headers(pnlOptions)
#include "wmbutton.h"
#include <wx/panel.h>
//*)

class FFTBuilder;
class SettingEvent;
class pnlOptions: public wxPanel
{
	public:

		pnlOptions(wxWindow* parent, FFTBuilder* pBuilder, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~pnlOptions();

        void SelectCursorMode(bool bSelect);
		//(*Declarations(pnlOptions)
		wmButton* m_pbtnFFT_Cursor;
		wmButton* m_pbtnFFT_Hold;
		//*)
		wmButton* m_pbtnFFT_Peak;
		wmButton* m_pbtnFFT_PeakReset;

	protected:

		//(*Identifiers(pnlOptions)
		static const long ID_M_PBTN1;
		static const long ID_M_PBTN34;
		//*)

		void OnSettingChanged(SettingEvent& event);
	private:

		//(*Handlers(pnlOptions)
		void OnbtnFFT_HoldClick(wxCommandEvent& event);
		void OnbtnFFT_CursorClick(wxCommandEvent& event);
		//*)

		void OnbtnFFT_PeakClick(wxCommandEvent& event);
		void OnbtnFFT_PeakResetClick(wxCommandEvent& event);

		FFTBuilder* m_pBuilder;
		DECLARE_EVENT_TABLE()
};

#endif
