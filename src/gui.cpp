#include <wx/filename.h>
#include <wx/colour.h>
#include <wx/image.h>
#include <iostream>
#include <thread>
#include <vector> 
#include <string> 
#include "Currency.h"
#include "Symbol.h"
#include "gui.h"
#include <unistd.h>

const int width = 300;
const int height = 350;
const int ID_Quit = 1;
const int ListBoxID = 2;
const int PanelID = 3;
const int wxID_ASK = 4;
const int wxID_BID = 5;

IMPLEMENT_APP(PriceApp);

std::string dataPath = "../";
std::string imgBasePath = dataPath + "images/";

bool PriceApp::OnInit()
{
    // Create main window frame    
    PriceFrame *priceFrame = new PriceFrame(wxT("Simple Market Watcher"));
    priceFrame->Show(true);
    return true;
}

BEGIN_EVENT_TABLE(PriceFrame, wxFrame)
    EVT_MENU(ID_Quit, PriceFrame::OnQuit)
    EVT_LISTBOX(ListBoxID, PriceFrame::OnListBoxSelect)
END_EVENT_TABLE()

// Main window frame 
PriceFrame::PriceFrame(const wxString &title) : 
wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(width, height))
{
    
    // Prepare symbols
    Symbol symbol;

    std::vector<Currency*> currencies; 

    currencies.push_back(new Currency("EUR", "USD"));
    currencies.push_back(new Currency("USD", "JPY"));
    currencies.push_back(new Currency("BTC", "USD"));

    currencies[0]->initiate();
    currencies[1]->initiate();
    currencies[2]->initiate();

    //Currency *eurusd = new Currency("EUR", "USD");
    //Currency *usdjpy = new Currency("USD", "JPY");
    //Currency *btcusd = new Currency("BTC", "USD");

    //eurusd->initiate();
    //usdjpy->initiate();
    //btcusd->initiate();

    // Menu bar
    wxMenu *menu = new wxMenu; 
    menu->Append(ID_Quit, _("E&xit"));
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menu, ("&File"));
    SetMenuBar(menuBar);
    this->CreateStatusBar();

    // Create the panel to place items on it 
    pricePanel = new PricePanel(this, currencies);
  
}

void PriceFrame::OnQuit(wxCommandEvent &event){
    Close(true);
}

void PriceFrame::OnListBoxSelect(wxCommandEvent &event){
    std::cout << "On List Box Select" << std::endl;
    this->pricePanel->SetText(pricePanel, "new value");
}

void PriceFrame::run(Symbol &symbol)
{
    while (true){
        std::string msg = symbol.showQueue();
        std::cout << "Price Chagned - " << msg <<std::endl;
    }
}

BEGIN_EVENT_TABLE(PricePanel, wxPanel)
    EVT_PAINT(PricePanel::paintEvent) // catch paint events
END_EVENT_TABLE()

PricePanel::PricePanel(wxFrame *parent, std::vector<Currency*> currencies) : 
wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_NONE)
{
    _currencies = currencies; 

    _name1 = _currencies[0]->getName();
    _name2 = _currencies[1]->getName();
    _name3 = _currencies[2]->getName();

    _price1 = _currencies[0]->getPrice(sideType::ask);
    _price2 = _currencies[1]->getPrice(sideType::ask); 
    _price3 = _currencies[2]->getPrice(sideType::ask); 

    _text1 = new wxStaticText(this, wxID_ANY, _name1, wxPoint(120, 20), wxSize(100, -1), wxALIGN_CENTRE | wxBORDER_SIMPLE);
    _text2 = new wxStaticText(this, wxID_ANY, _name2, wxPoint(120, 70), wxSize(100, -1), wxALIGN_CENTRE | wxBORDER_SIMPLE);
    _text3 = new wxStaticText(this, wxID_ANY, _name3, wxPoint(120, 120), wxSize(100, -1), wxALIGN_CENTRE | wxBORDER_SIMPLE);

    _text1->SetForegroundColour("White");
    _text2->SetForegroundColour("Black");
    _text3->SetForegroundColour("Black");
   
    _priceText1 = new wxTextCtrl(this, wxID_ANY, std::to_string(_price1), wxPoint(190, 20), wxSize(100, 20),wxTE_READONLY);
    _priceText2 = new wxTextCtrl(this, wxID_ANY, std::to_string(_price2), wxPoint(190, 70), wxSize(100, 20),wxTE_READONLY);
    _priceText3 = new wxTextCtrl(this, wxID_ANY, std::to_string(_price3), wxPoint(190, 120), wxSize(100, 20),wxTE_READONLY);

    wxButton *button_ask = new wxButton(this, wxID_ASK, _("Ask"), wxPoint(70, 230));
    wxButton *button_bid = new wxButton(this, wxID_BID, _("Bid"), wxPoint(160, 230));

    Connect(wxID_ASK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PricePanel::selectAsk));
    Connect(wxID_BID, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PricePanel::selectBid));
   
}

void PricePanel::SetText(PricePanel *panel, wxString text){
    std::cout << "setText():" << text  <<  std::endl;
    //_priceText1 = new wxTextCtrl(this, wxID_ANY, text, wxPoint(150, 160), wxSize(130, 20),wxTE_READONLY);

    //std::cout << "_price1 address: " << &this->_price1 << std::endl; 
    std::cout << "_price1 value: " << this->_price1 << std::endl;
    _priceText1->SetValue(text);
}

void PricePanel::selectAsk(wxCommandEvent &event){
    _price1 = _currencies[0]->getPrice(sideType::ask);
    _price2 = _currencies[1]->getPrice(sideType::ask); 
    _price3 = _currencies[2]->getPrice(sideType::ask); 

    _priceText1 = new wxTextCtrl(this, wxID_ANY, std::to_string(_price1), wxPoint(190, 20), wxSize(100, 20),wxTE_READONLY);
    _priceText2 = new wxTextCtrl(this, wxID_ANY, std::to_string(_price2), wxPoint(190, 70), wxSize(100, 20),wxTE_READONLY);
    _priceText3 = new wxTextCtrl(this, wxID_ANY, std::to_string(_price3), wxPoint(190, 120), wxSize(100, 20),wxTE_READONLY);
}

void PricePanel::selectBid(wxCommandEvent &event){
    _price1 = _currencies[0]->getPrice(sideType::bid);
    _price2 = _currencies[1]->getPrice(sideType::bid); 
    _price3 = _currencies[2]->getPrice(sideType::bid); 

    _priceText1 = new wxTextCtrl(this, wxID_ANY, std::to_string(_price1), wxPoint(190, 20), wxSize(100, 20),wxTE_READONLY);
    _priceText2 = new wxTextCtrl(this, wxID_ANY, std::to_string(_price2), wxPoint(190, 70), wxSize(100, 20),wxTE_READONLY);
    _priceText3 = new wxTextCtrl(this, wxID_ANY, std::to_string(_price3), wxPoint(190, 120), wxSize(100, 20),wxTE_READONLY);
}

void PricePanel::paintEvent(wxPaintEvent &evt)
{
    wxPaintDC dc(this);
    render(dc);
}

void PricePanel::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

void PricePanel::render(wxDC &dc)
{
    // load backgroud image from file
    wxImage image;
    wxInitAllImageHandlers();
    image.LoadFile(imgBasePath + "background.jpg", wxBITMAP_TYPE_JPEG );

    // rescale image to fit window dimensions
    wxSize sz = this->GetSize();    
    wxImage imgSmall = image.Rescale(sz.GetWidth(), sz.GetHeight(), wxIMAGE_QUALITY_HIGH);
    _image = wxBitmap(imgSmall);

    dc.DrawBitmap(_image, 0, 0, false);

}
