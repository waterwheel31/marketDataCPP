cmake_minimum_required(VERSION 3.11.3)

# set(CMAKE_CXX_STANDARD 17)
project(OSM_A_star_search)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")

SET(OpenCV_DIR "/home/c/dev/opencv-4.1.0/build")    
find_package(OpenCV 4.1 REQUIRED PATHS "/home/c/dev/opencv-4.1.0/build")

SET(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED) 
include_directories(${CURL_INCLUDE_DIR})

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

SET(jsoncpp_LIBRARY "-ljsoncpp") 
find_package(jsoncpp REQUIRED)
include_directories( ${jsoncpp_INCLUDE_DIRS} )

# Find all executables
file(GLOB project_SRCS src/*.cpp) #src/*.h

# Add project executable
add_executable(marketWatcher ${project_SRCS})
target_link_libraries(marketWatcher ${OpenCV_LIBRARIES})
target_link_libraries(marketWatcher ${CURL_LIBRARIES})
target_link_libraries(marketWatcher ${jsoncpp_LIBRARIES})