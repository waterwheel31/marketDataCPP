#ifndef SYMBOL_H
#define SYMBOL_H 

#include <iostream>
#include <string> 
#include <mutex>
#include <deque>
#include <thread>
#include <vector>
#include <condition_variable>


//template <class T>
class MessageQueue {
    public: 
        std::string receive();
        void send(std::string &&msg);
    private: 
        std::mutex _mtx;
        std::condition_variable _cond;
        std::deque<std::string> _queue; 
};



class Symbol {
    public:
        // Currency(std::string name1, std::string name2);   // constructor
        Symbol();
        ~Symbol();  // deconstructor     

        std::string getName();
        void showQueue();

        std::vector<std::thread> threads;
        std::shared_ptr<MessageQueue> _queueSYM;
        std::thread th; 

    private: 
        
        void setShared(std::shared_ptr<MessageQueue> msq);
        std::string _name;   

                  
};

#endif