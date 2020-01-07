#ifndef GUI_H_
#define GUI_H_

#include <wx/wx.h>
#include <wx/listbox.h>
#include <memory>
#include "Symbol.h"


class PricePanel : public wxPanel
{
    private: 
        wxBitmap _image;

    public: 
        float _price1 = 0;
        float _price2 = 0;
        wxStaticText *_text1;
        wxStaticText *_text2;
        wxTextCtrl *_priceText1;
        wxTextCtrl *_priceText2;
        
        PricePanel(wxFrame *parent);
        void SetText(PricePanel *panel, wxString text);

        void paintEvent(wxPaintEvent &evt);
        void paintNow();
        void render(wxDC &dc);

        DECLARE_EVENT_TABLE()
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