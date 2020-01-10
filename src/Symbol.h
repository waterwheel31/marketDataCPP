#ifndef SYMBOL_H
#define SYMBOL_H 

#include <iostream>
#include <string> 
#include <mutex>
#include <deque>
#include <thread>
#include <vector>
#include <condition_variable>


template <class T>
class MessageQueue {
    public: 
        T receive();
        static void send(T &&msg);
    private: 
        std::mutex _mtx;
        std::condition_variable _cond;
        std::deque<T> _queue; 
};



class Symbol {
    public:
        // Currency(std::string name1, std::string name2);   // constructor
        Symbol();
        ~Symbol();  // deconstructor     

        std::string getName();
        std::string showQueue();

        std::vector<std::thread> threads;

    private: 
    
        void setShared(std::shared_ptr<MessageQueue<std::string>> msq);
        std::string _name;   

                  
};

#endif