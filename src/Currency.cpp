#include <iostream>
#include <string> 
#include <mutex>
#include <deque>
#include <thread>
#include <vector>
#include <future>
#include <condition_variable>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <memory> 


#include "Currency.h"
#include "Symbol.h"
#include <curl/curl.h> 


Currency::Currency(const std::string name1, const std::string name2){
    _name1 = name1; 
    _name2 = name2;  
    _name = _name1 + _name2;   
}

Currency::~Currency(){
    th.join();
}

void Currency::initiate(){
    
    std::cout << _name << ": initiated" << std::endl; 
    
    CURL *curl;
    CURLcode res;
    std::string body; 
    std::string API = std::getenv("ALPHAAPI");
    std::string url = "https://www.alphavantage.co/query?function=CURRENCY_EXCHANGE_RATE&from_currency=BTC&to_currency=CNY&apikey=" + API; 
    
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    //curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);
    curl_easy_perform(curl);
    int httpCode = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    // std::cout << res << std::endl; 
    
    std::cout << "httpCode:" << httpCode << std::endl;
    if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
    if (httpCode==200){
       
        //std::string res_s = std::to_string(res);
        //std::stringstream res_ss(res_s);

        std::cout << body << std::endl;

        std::string out;

        //std::cout << res_s << std::endl;

        /*
        while (res_ss >> out){
            std::cout << "before" << std::endl;
            std::cout << out << std::endl;
            std::cout << "after" << std::endl;
        }
        */

        
        
    }
    


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