# Simple Market Price Watcher

## What is this? 

- sample image 

- This is a simple widget to retrive market prices from a website (`Alphavantage.co`)
- Data is updated through REST API. This is not realtime, and requests prices only periodically (default = every 10 minutes)


## Libraries Used

- cMake - for compiling 

- WxWidgets - for GUI 
- LibCurl - for HTTP requests


## How to Run? 

- Install libraries above (see the websites of the libraries for install details)
- Set environment variable "ALPHAAPI". Type: `export ALPHAAPI=<YOUR API KEY>` at Linux command line. To get your API key, go to `Alphavantage.co`
- Type: `mkdir build && cd build && cmake..`  
- Compile the program. Type: `make` at `build` directory 
- Run the program. Type: `./marketWatcher` at `build` directory 
- Then the program automatically retrive the prices from `Alphavantage.co` and update the prices 
- To exit, click `file` at the top of the window and click `exit` 
- By clicking buttons on the window, you can chagne the price sides (ask, bid) 


## Tested OS

- This program is developed and tested on Ubuntu 18.04 
