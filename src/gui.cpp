#include <wx/filename.h>
#include <wx/colour.h>
#include <wx/image.h>

#include <thread>
#include <vector> 
#include <string> 
#include "Currency.h"
#include "Symbol.h"
#include "gui.h"

const int width = 300;
const int height = 300;

IMPLEMENT_APP(PriceApp);

bool PriceApp::OnInit()
{
    // create window with name and show it
    std::cout << "ChatBotApp::OnInit() \n";
    PriceFrame *priceFrame = new PriceFrame(wxT("Market Watcher"));
    priceFrame->Show(true);

    Symbol symbol;

    std::string name1 = "USD";
    std::string name2 = "JPY";
    std::string name3 = "EUR";
    
    Currency *usdjpy = new Currency(name1, name2);
    Currency *eurjpy = new Currency(name3, name2);

    usdjpy->initiate();
    usdjpy->setShared(symbol._queueSYM);
    eurjpy->initiate();
    eurjpy->setShared(symbol._queueSYM);

    priceFrame->run(symbol);

    //while(true){}

    
    return true;
}

PriceFrame::PriceFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(width, height))
{
    // position window in screen center
    wxString text = "test";
    PriceItem *priceItem = new PriceItem(this,text);
    this->Centre();
}

void PriceFrame::run(Symbol &symbol)
{
    while (true){
        std::string msg = symbol.showQueue();
        std::cout << "Price Chagned - " << msg <<std::endl;
        //priceFrame->priceItem->setText(priceFrame, msg);
    }
}

PriceItem::PriceItem(wxFrame *parent, wxString text) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_NONE)
{
    _text1 = new wxStaticText(this, wxID_ANY, text, wxPoint(-1, -1), wxSize(300, -1), wxALIGN_CENTRE | wxBORDER_NONE);
    _text1->Wrap(150);
}

void PriceItem::setText(wxFrame *parent, wxString text){
    //_text1 = new wxStaticText(parent, wxID_ANY, text, wxPoint(-1, -1), wxSize(300, -1), wxALIGN_CENTRE | wxBORDER_NONE);
    //_text1.SetLabel(text);
    //_text1->SetLabel(text);
    std::cout << "setText()" << std::endl;

}

