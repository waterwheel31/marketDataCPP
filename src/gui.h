#ifndef GUI_H_
#define GUI_H_

#include <wx/wx.h>
#include <wx/listbox.h>
#include <memory>
#include "Symbol.h"


class PricePanel : public wxPanel
{
    private: 
        wxStaticText *_text1;
        wxStaticText *_text2;
        wxTextCtrl *_priceText1;
        wxTextCtrl *_priceText2;

    public: 
        PricePanel(wxFrame *parent, wxString text);
        void SetText(wxFrame *parent, wxString text);
};

// frame containing all control elements
class PriceFrame : public wxFrame
{
    private:
        // control elements
        wxTextCtrl *_userTextCtrl;

        // events
        void OnEnter(wxCommandEvent &WXUNUSED(event));
        Symbol _symbol; 
 
    public:
        // constructor / desctructor
       PriceFrame(const wxString &title);
       PricePanel *pricePanel;
       void run(Symbol &symbol);
       void OnQuit(wxCommandEvent &event);
       void OnListBoxSelect(wxCommandEvent &event);
       DECLARE_EVENT_TABLE()
};

// wxWidgets app that hides main()
class PriceApp : public wxApp
{
public:
    // events
    bool OnInit();

};

#endif /* GUI_H_ */