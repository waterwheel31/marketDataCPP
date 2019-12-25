#ifndef SYMBOL_H
#define SYMBOL_H 

#include <iostream>
#include <string> 
#include <mutex>
#include <deque>
#include <condition_variable>

enum sideType {ask, bid};



class Currency {

    public:
        // Currency(std::string name1, std::string name2);   // constructor
       //  Currency();
        // ~Currency();  // deconstructor
        //Currency(const Currency &source);  // copy constructor
        //Currency(const Currency &&source); // move constractor
        //Currency &operator=(const Currency &source);  // assignment operator
        //Currency &operator=(const Currency &&source);  // move assignment operator 

        float getPrice(sideType);
        std::string getName();

    private: 
        float _bid; 
        float _ask;

        std::string _name1;
        std::string _name2;

        void updatePrice();

};

#endif