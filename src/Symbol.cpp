#include <iostream>
#include <string> 
#include <thread>
#include <random>  
#include <vector>

#include <curl/curl.h> 
#include "Symbol.h"

std::string MessageQueue::receive(){
    //std::cout <<  "step 1" << std::endl;
    std::unique_lock<std::mutex> uLock(_mtx);
    //std::cout <<  "step 2" << std::endl;
    _cond.wait(uLock, [this] { return !_queue.empty(); });
    //std::cout <<  "step 3" << std::endl;
    std::string msg = std::move(_queue.back());    
    //std::cout <<  "step 4" << std::endl;
    _queue.pop_back();
    //std::cout <<  "step 5" << std::endl;
    return msg;
}
void MessageQueue::send(std::string &&msg){
    std::lock_guard<std::mutex> uLock(_mtx);
    _queue.push_back(std::move(msg));
    _cond.notify_one();
}


std::mutex Symbol::_mtx;

Symbol::Symbol(){
    _queueSYM = std::make_shared<MessageQueue>();
}   
Symbol::~Symbol(){}   


std::string Symbol::showQueue(){
    //std::cout << "showQueue() before " <<std::endl;
    auto message = _queueSYM->receive();
    //std::cout << "showQueue() after" <<std::endl;
    //std::cout<< "queue:" << message << std::endl;
    return message;
}

void Symbol::setShared(std::shared_ptr<MessageQueue> msq){
    _queueSYM = msq;
}
  
std::string Symbol::getName(){
    return _name; 
}
