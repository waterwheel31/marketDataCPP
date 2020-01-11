#include <iostream>
#include <string> 
#include <thread>
#include <random>  
#include <vector>

#include <curl/curl.h> 
#include "Symbol.h"

//template <class T> 
std::string MessageQueue::receive(){
    std::cout << "message received" << std::endl;
    std::cout <<  "step 1" << std::endl;
    std::unique_lock<std::mutex> uLock(_mtx);
    std::cout <<  "step 2" << std::endl;
    _cond.wait(uLock, [this] { return !_queue.empty(); });
    std::cout <<  "step 3" << std::endl;
    std::string msg = std::move(_queue.back());    
    std::cout <<  "step 4" << std::endl;
    _queue.pop_back();
    std::cout <<  "step 5" << std::endl;
    return msg;
}

//template <class T> 
void MessageQueue::send(std::string &&msg){
    std::lock_guard<std::mutex> uLock(_mtx);
    _queue.push_back(std::move(msg));
    _cond.notify_one();
}

//std::mutex Symbol::_mtx;

Symbol::Symbol(){
    std::thread th(&Symbol::showQueue, this);
    //_queueSYM = std::make_shared<MessageQueue<std::string>>();
    th.join();
}   
Symbol::~Symbol(){ 
    th.join();
}

void Symbol::showQueue(){
    while(true){
        auto message = _queueSYM->receive();
    }
    
    
}

void Symbol::setShared(std::shared_ptr<MessageQueue> msq){
    _queueSYM = msq;
}
  
std::string Symbol::getName(){
    return _name; 
}
