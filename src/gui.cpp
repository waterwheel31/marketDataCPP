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

    const std::string name1 = "USD";
    const std::string name2 = "JPY";
    const std::string name3 = "EUR";
    const std::string name4 = "BTC";
    
    Currency *usdjpy = new Currency(name1, name2);
    Currency *eurjpy = new Currency(name3, name2);
    Currency *btcusd = new Currency(name4, name1);

    //Currency usdjpy(name1, name2);
    //Currency eurjpy(name3, name2);
    //Currency btcusd(name4, name1);

    usdjpy->initiate();
    //eurjpy->initiate();
    //btcusd->initiate();
    //usdjpy->setShared(symbol._queueSYM);
    
    //std::vector<std::shared_ptr<Currency>> curVec; 
    //curVec.push_back(std::shared_ptr<Currency>(usdjpy));
    //curVec.push_back(std::shared_ptr<Currency>(eurjpy));
    //curVec.push_back(std::shared_ptr<Currency>(btcusd));
   

    // Menu bar
    wxMenu *menu = new wxMenu; 
    menu->Append(ID_Quit, _("E&xit"));
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menu, ("&File"));
    SetMenuBar(menuBar);
    this->CreateStatusBar();

    // Create the panel to place items on it 
    pricePanel = new PricePanel(this);
  
    // Create an Exit button  
    /*
    wxButton *button = new wxButton(pricePanel, wxID_EXIT, _("Exit"), wxPoint(25, 30));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PriceFrame::OnQuit));
    button->SetFocus();
    */

    // Create a list of symbols 
    wxListBox *listBox = new wxListBox(pricePanel, ListBoxID, wxPoint(150,30),wxSize(130, 100));
    this->Connect(ListBoxID, wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(PriceFrame::OnListBoxSelect));

    //listBox->Append(usdjpy->getName());
    listBox->Append("EURJPY");
    listBox->Append("BTCUSD");

    this->Centre();
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

void PriceFrame::OnEnter(wxCommandEvent &WXUNUSED(event))
{
    std::cout << "Enter" << std::endl;
    //std::string msg = _symbol.showQueue();
    //std::cout << "Price Chagned - " << msg <<std::endl;
}


BEGIN_EVENT_TABLE(PricePanel, wxPanel)
    EVT_PAINT(PricePanel::paintEvent) // catch paint events
END_EVENT_TABLE()

PricePanel::PricePanel(wxFrame *parent) : 
wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_NONE)
{
     _price1 = 0.1;
     _price2 = 0.2; 

    //std::cout << "_price1 address: " << &this->_price1  << std::endl;

    _text1 = new wxStaticText(this, wxID_ANY, "Bid Price:", wxPoint(30, 160), wxSize(100, -1), wxALIGN_CENTRE | wxBORDER_SIMPLE);
    _text2 = new wxStaticText(this, wxID_ANY, "Ask Price:", wxPoint(30, 200), wxSize(100, -1), wxALIGN_CENTRE | wxBORDER_SIMPLE);

    _priceText1 = new wxTextCtrl(this, wxID_ANY, std::to_string(_price1), wxPoint(150, 160), wxSize(130, 20),wxTE_READONLY);
    _priceText2 = new wxTextCtrl(this, wxID_ANY, std::to_string(_price2), wxPoint(150, 200), wxSize(130, 20),wxTE_READONLY);
   
}

void PricePanel::SetText(PricePanel *panel, wxString text){
    std::cout << "setText():" << text  <<  std::endl;
    //_priceText1 = new wxTextCtrl(this, wxID_ANY, text, wxPoint(150, 160), wxSize(130, 20),wxTE_READONLY);
    
    //std::cout << "_price1 address: " << &this->_price1 << std::endl; 
    std::cout << "_price1 value: " << this->_price1 << std::endl;
    _priceText1->SetValue(text);
    
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
