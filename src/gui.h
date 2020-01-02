#ifndef GUI_H_
#define GUI_H_

#include <wx/wx.h>
#include <memory>
#include "Symbol.h"


class PriceItem : public wxPanel
{
    private: 
        wxStaticText *_text1;
        wxStaticText *_text2;
    public: 
        PriceItem(wxFrame *parent, wxString text);
        void setText(wxFrame *parent, wxString text);
};

// frame containing all control elements
class PriceFrame : public wxFrame
{
    private:
        // control elements
        wxTextCtrl *_userTextCtrl;

        // events
        void OnEnter(wxCommandEvent &WXUNUSED(event));
 
    public:
        // constructor / desctructor
       PriceFrame(const wxString &title);
       PriceItem *priceItem;
       void run(Symbol &symbol);
};

// wxWidgets app that hides main()
class PriceApp : public wxApp
{
public:
    // events
    bool OnInit();

};

#endif /* GUI_H_ */