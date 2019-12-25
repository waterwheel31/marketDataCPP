#include <iostream> 
#include <thread>
#include <vector> 
#include <string> 
#include "Symbol.h"


int main(){
    std::cout << "market watcher start \n"; 
    
    std::string name1 = "USD";
    std::string name2 = "JPY";

    Currency usdjpy(name1, name2);

    std::cout << "name: " << usdjpy.getName() << "\n"; 

    return 0;

}