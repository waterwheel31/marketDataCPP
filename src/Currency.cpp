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
#include <regex> 


#include "Currency.h"
#include "Symbol.h"
#include <curl/curl.h> 



struct Buffer { 
    char *data;
    int data_size; 
};

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
    updatePrice();
    threads.emplace_back(std::thread(&Currency::runProcess, this));
  
}

int Currency::write_callback(char *ptr, size_t size, size_t nmemb, char *res){
    std::cout << "call back function" << std::endl;
    
    struct Buffer *buf = (struct Buffer *)res; 
    int block = size * nmemb; 
    buf->data = (char *)realloc(buf->data, buf->data_size + block);
    memcpy(buf->data + buf->data_size, ptr, block);
    buf->data_size += block;
    return 0;
}

void Currency::updatePrice(){
    
    CURL *curl;
    CURLcode code;

    struct Buffer *buf;

    buf = (struct Buffer *)malloc(sizeof(struct Buffer));
    buf->data = NULL;
    buf->data_size = 0;

    std::string API = std::getenv("ALPHAAPI");
    std::cout << "_name1:" << _name1 << " _name2: " << _name2 << std::endl; 
    std::string url = "https://www.alphavantage.co/query?function=CURRENCY_EXCHANGE_RATE&from_currency=" + _name1 + "&to_currency=" + _name2 + "&apikey=" + API; 
    //std::cout << url << std::endl; 
    
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, buf);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_perform(curl);

    int httpCode = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    //std::cout << "httpCode:" << httpCode << std::endl;

    if(code != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(code));
        }
    if (httpCode==200){
       
        std::string line;
        std::stringstream stream(buf->data);
        
        while(std::getline(stream, line)){
            if (line.find("8. Bid Price") != std::string::npos){
                //std::cout  <<  line << std::endl;
                std::regex re("\\d+.\\d+");
                std::smatch m;
                while(std::regex_search(line, m, re )){
                    //std::cout  <<  m.str() << std::endl;
                    _bid = std::stod(m.str()); 
                    line = m.suffix();
                }
                
            }
            if (line.find("9. Ask Price") != std::string::npos){
                //std::cout  <<  line << std::endl;
                std::regex re("\\d+.\\d+");
                std::smatch m;
                while(std::regex_search(line, m, re )){
                    //std::cout  <<  m.str() << std::endl;
                    _ask = std::stod(m.str()); 
                    line = m.suffix();
                }
            }
        }
    }
    std::cout << "ask: " << _ask  << " bid: " << _bid  << std::endl; 
}

void Currency::runProcess(){
    while(true){
        _ask++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::unique_lock<std::mutex> lck(_mtx);

        std::string  message = _name1 + _name2 + ": " + std::to_string(_ask); 
        auto is_sent = std::async(std::launch::async, &MessageQueue::send, _queueSYM, std::move(message));
        is_sent.wait();

        lck.unlock();
    }
}

std::string Currency::getName(){
    return _name1 + _name2; 
}