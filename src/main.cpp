#include <iostream> 
#include <thread>
#include <vector> 
#include <string> 
#include "Currency.h"
#include "Symbol.h"


int main(){
    std::cout << "market watcher start \n"; 
   
    Symbol symbol;

    std::string name1 = "USD";
    std::string name2 = "JPY";
    std::string name3 = "EUR";

    Currency usdjpy(name1, name2);
    Currency eurjpy(name3, name2);

    //std::cout << "name: " << usdjpy.getName() << "\n"; 

    usdjpy.initiate();
    eurjpy.initiate();

    //std::thread t1(symbol.showQueue());

    while (true){
        //auto text = usdjpy._queue->receive();
        std::cout << symbol.showQueue();
        
    }
    
    //std::thread th(usdjpy.initiate);

    return 0;

}