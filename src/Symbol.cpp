#include <iostream>
#include <string> 
#include <thread>
#include <random>  
#include <vector>

#include <curl/curl.h> 
#include "Symbol.h"

std::string API = std::getenv("AlphaAPI");

Currency::Currency(std::string name1, std::string name2){
    _name1 = name1;
    _name2 = name2;

   
    initiate();
    
}

Currency::~Currency(){
}

std::string Currency::getName(){
    return _name1 + _name2; 
}

void Currency::initiate(){
    std::cout << "intiate()" << std::endl;
    std::thread t1(&Currency::runProcess, this);
    //std::thread t([]{std::cout << "thread" << std::endl;});
    // std::thread t(runProcess);
    // threads.push_back(std::thread(&Currency::runProcess, this));

}


void Currency::runProcess(){
    std::cout << "run process" << std::endl; 
    /*
    while(true){
        updatePrice();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000*1));
    }
    */
    
}

void Currency::updatePrice(){
    //std::cout << "updating the price \n"; 
    CURL *curl;
    CURLcode res;

    float newbid, newask; 
    
    std::string url = "https://www.alphavantage.co/query?function=CURRENCY_EXCHANGE_RATE&from_currency=BTC&to_currency=CNY&apikey=" + API; 

    /*
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        res = curl_easy_perform(curl);
        int httpCode = 0;
        //Json::Reader jsonReader; 
        //Json::Value jsonData;
        //std::unique_ptr<std::string> httpData(new std::string());
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        if (httpCode ==200){  
            
                std::string rString; 
                std::cout << res << std::endl; 
            

        }
        curl_easy_cleanup(curl);

    }
    */
    std::random_device rd; 
    newbid = 100.0 + rd() % 10 ;   // dummy 
    newask = newbid + rd() %10 /10.0 ; 

    if(_bid != newbid || _ask != newask){
        std::cout << "priced changed " << "ask:" << _ask << " bid:" << _bid <<  std::endl; 
    }

   _bid = newbid;
   _ask = newask;

}
