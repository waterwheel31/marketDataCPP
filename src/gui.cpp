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
const int ID_Quit = 1;
const int ListBoxID = 1;

IMPLEMENT_APP(PriceApp);



bool PriceApp::OnInit()
{
    // create window with name and show it
    std::cout << "ChatBotApp::OnInit() \n";
    
    //wxButton *button = new wxButton(_("Button"), wxSize(250, 100));
    //button->Show();

    Symbol symbol;

    PriceFrame *priceFrame = new PriceFrame(wxT("Market Watcher"));
    priceFrame->Show(true);

    std::string name1 = "USD";
    std::string name2 = "JPY";
    std::string name3 = "EUR";
    
    Currency *usdjpy = new Currency(name1, name2);
    Currency *eurjpy = new Currency(name3, name2);

    usdjpy->initiate();
    usdjpy->setShared(symbol._queueSYM);
    eurjpy->initiate();
    eurjpy->setShared(symbol._queueSYM);

    //while (true){
        //std::string msg = symbol.showQueue();
        //std::cout << "Price Chagned - " << msg <<std::endl;
        //priceFrame->Show(true);
    //}

    return true;
}

PriceFrame::PriceFrame(const wxString &title) : 
wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(width, height))
{
    // position window in screen center
    wxString text = "text";
    wxMenu *menu = new wxMenu; 
    menu->Append(ID_Quit, _("E&xit"));

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menu, ("&File"));
    SetMenuBar(menuBar);
    this->CreateStatusBar();

    PricePanel *pricePanel = new PricePanel(this,text);
  
    //wxPanel *panel = new wxPanel(this, wxID_ANY);
    wxButton *button = new wxButton(pricePanel, wxID_EXIT, _("Exit"), wxPoint(25, 30));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PriceFrame::OnQuit));
    button->SetFocus();

    wxListBox *listBox = new wxListBox(pricePanel, ListBoxID, wxPoint(150,30),wxSize(130, 100));
    Connect(ListBoxID, wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(PriceFrame::OnListBoxSelect));

    listBox->Append("USDJPY");
    listBox->Append("EURJPY");
    listBox->Append("BTCUSD");
    
    //this->Connect(id,  wxEVT_TEXT_ENTER, wxCommandEventHandler(PriceFrame::OnEnter));
        
    //wxBoxSizer *vertBoxSizer = new wxBoxSizer(wxVERTICAL);
    //vertBoxSizer->AddSpacer(90);

    

    this->Centre();
}




BEGIN_EVENT_TABLE(PriceFrame, wxFrame)
    EVT_MENU(ID_Quit, PriceFrame::OnQuit)
END_EVENT_TABLE()

void PriceFrame::OnQuit(wxCommandEvent &event){
    Close(true);
}

void PriceFrame::OnListBoxSelect(wxCommandEvent &event){
    std::cout << "On List Box Select" << std::endl;
    pricePanel->SetText(this, "new value");
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

PricePanel::PricePanel(wxFrame *parent, wxString text) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_NONE)
{
    float _price1 = 0;
    float _price2 = 0; 

    _text1 = new wxStaticText(this, wxID_ANY, "Bid Price:", wxPoint(30, 160), wxSize(100, -1), wxALIGN_CENTRE | wxBORDER_SIMPLE);
    _text2 = new wxStaticText(this, wxID_ANY, "Ask Price:", wxPoint(30, 200), wxSize(100, -1), wxALIGN_CENTRE | wxBORDER_SIMPLE);

    _priceText1 = new wxTextCtrl(this, wxID_ANY, std::to_string(_price1), wxPoint(150, 160), wxSize(130, 20),wxTE_READONLY);
    _priceText2 = new wxTextCtrl(this, wxID_ANY, std::to_string(_price2), wxPoint(150, 200), wxSize(130, 20),wxTE_READONLY);
   
}

void PricePanel::SetText(wxFrame *parent, wxString text){
    std::cout << "setText():" << text <<  std::endl;
    std::cout << "_priceText1:" << this->_priceText1 <<  std::endl;
    _priceText1->SetValue("text");
    
}

