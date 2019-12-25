#include <iostream> 
#include <thread>
#include <vector> 
#include <string> 
#include "symbol.h"


int main(){
    std::cout << "market watcher start \n"; 
    
    std::string name1 = "USD";
    std::string name2 = "JPY";

    //Currency USDJPY(name1, name2);
    Currency usdjpy;

    std::cout << usdjpy.getName() << "\n"; 

    return 0;

}