#ifndef CURRENCY_H
#define CURRENCY_H 

#include <iostream>
#include <string> 
#include <mutex>
#include <deque>
#include <thread>
#include <vector>
#include <condition_variable>

#include "Symbol.h"


enum sideType {ask, bid};



class Currency: public Symbol, public std::enable_shared_from_this<Currency> {

    public:
        // Currency(std::string name1, std::string name2);   // constructor
        Currency(std::string name1, std::string name2);
        ~Currency();  // deconstructor
        Currency(const Currency &source);  // copy constructor
        Currency(const Currency &&source); // move constractor
        Currency &operator=(const Currency &source);  // assignment operator
        Currency &operator=(const Currency &&source);  // move assignment operator 

        float getPrice(sideType);
        std::string getName();
        void initiate();
        void runProcess();

        std::shared_ptr<Currency> get_shared_this() { return shared_from_this(); }

       
    private: 
        float _bid; 
        float _ask;

        std::thread th; 

        std::string _name1;
        std::string _name2;
        
        void updatePrice();
       
    protected:
        
};

#endif