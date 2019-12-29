#include <iostream>
#include <string> 
#include <thread>
#include <random>  
#include <vector>

#include <curl/curl.h> 
#include "Symbol.h"



std::string MessageQueue::receive(){
    std::unique_lock<std::mutex> uLock(_mtx);
    _cond.wait(uLock, [this] { return !_queue.empty(); });
    std::string msg = std::move(_queue.back());    
    _queue.pop_back();
    return msg;
}
void MessageQueue::send(std::string &&msg){
    std::lock_guard<std::mutex> uLock(_mtx);
    _queue.push_back(std::move(msg));
    _cond.notify_one();

}

std::mutex Symbol::_mtx;

Symbol::Symbol(){
    _queue = std::make_shared<MessageQueue>();
}   
Symbol::~Symbol(){}   


std::string Symbol::showQueue(){
    auto message = _queue->receive();
    std::cout << "showQueue()" <<std::endl;
    return message;
}
  
