#include <iostream> 
#include <thread>
#include <vector> 
#include <string> 
#include "Currency.h"
#include "Symbol.h"
#include "gui.h"

/*
int main(){
    std::cout << "market watcher start \n"; 
   
    Symbol symbol;

    PriceFrame *pFrame = new PriceFrame(wxT("Market Price"));
    pFrame->Show(true);

    std::string name1 = "USD";
    std::string name2 = "JPY";
    std::string name3 = "EUR";

    Currency usdjpy(name1, name2);
    Currency eurjpy(name3, name2);

    usdjpy.initiate();
    usdjpy.setShared(symbol._queueSYM);
    eurjpy.initiate();
    eurjpy.setShared(symbol._queueSYM);


    while (true){
        std::string msg = symbol.showQueue();
        std::cout << "Price Chagned - " <<msg <<std::endl;
    }
    

    return 0;

}
*/