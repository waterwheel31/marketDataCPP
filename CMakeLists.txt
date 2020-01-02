cmake_minimum_required(VERSION 3.11.3)

# set(CMAKE_CXX_STANDARD 17)
project(marketWatcher)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")

SET(CURL_LIBRARY "-lcurl") 

find_package(CURL REQUIRED) 
find_package(wxWidgets REQUIRED COMPONENTS core base)

include_directories(${CURL_INCLUDE_DIR})
include(${wxWidgets_USE_FILE})

# Find all executables
file(GLOB project_SRCS src/*.cpp) #src/*.h

# Add project executable
add_executable(marketWatcher ${project_SRCS})
target_link_libraries(marketWatcher ${CURL_LIBRARIES})
target_link_libraries(marketWatcher ${wxWidgets_LIBRARIES})

target_include_directories(marketWatcher PRIVATE ${wxWidgets_INCLUDE_DIRS})