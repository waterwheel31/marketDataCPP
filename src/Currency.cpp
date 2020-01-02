
#include <iostream>
#include <string> 
#include <mutex>
#include <deque>
#include <thread>
#include <vector>
#include <future>
#include <condition_variable>

#include "Currency.h"
#include "Symbol.h"


Currency::Currency(std::string name1, std::string name2){
    _name1 = name1; 
    _name2 = name2;     
    //initiate();
}

Currency::~Currency(){
    th.join();
}

void Currency::initiate(){
    std::cout << _name1 + _name2 << ": initiateed" << std::endl; 
    //th = std::thread(&Currency::runProcess, this);

    threads.emplace_back(std::thread(&Currency::runProcess, this));
    //_queue = std::make_shared<MessageQueue>();
  
}

void Currency::runProcess(){
    while(true){
        _ask++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::unique_lock<std::mutex> lck(_mtx);
        // std::cout <<  _name1 + _name2 << ": " << _ask << std::endl;

        std::string  message = _name1 + _name2 + ": " + std::to_string(_ask); 
        auto is_sent = std::async(std::launch::async, &MessageQueue::send, _queueSYM, std::move(message));
        is_sent.wait();
        //std::cout <<"message sent" << std::endl;

        lck.unlock();
    }
}

std::string Currency::getName(){
    return _name1 + _name2; 
}