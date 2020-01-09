#ifndef GUI_H_
#define GUI_H_

#include <wx/wx.h>
#include <wx/listbox.h>
#include <memory>
#include <vector> 
#include <string> 
#include "Currency.h"
#include "Symbol.h"


class PricePanel : public wxPanel
{
    private: 
        wxBitmap _image;

        std::vector<Currency*> _currencies;

        std::string _name1;
        std::string _name2;
        std::string _name3;
        float _price1 = 0;
        float _price2 = 0;
        float _price3 = 0;

        wxStaticText *_text1;
        wxStaticText *_text2;
        wxStaticText *_text3;
        wxTextCtrl *_priceText1;
        wxTextCtrl *_priceText2;
        wxTextCtrl *_priceText3;

    public: 
        
        PricePanel(wxFrame *parent, std::vector<Currency*> currencies);
        void SetText(PricePanel *panel, wxString text);
        void UpdateText(sideType side, std::vector<Currency*> currencies); 

        void paintEvent(wxPaintEvent &evt);
        void paintNow();
        void render(wxDC &dc);
        void selectAsk(wxCommandEvent &event);
        void selectBid(wxCommandEvent &event);

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