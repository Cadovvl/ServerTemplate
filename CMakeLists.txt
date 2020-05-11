cmake_minimum_required(VERSION 3.5.1)
project(Server)

ADD_DEFINITIONS(
        -std=c++14
        -Wall
        -O2
)

set(SOURCE_FILES main.cpp
  MainListener.cpp 
  MainListener.h 
  src/EntityRequestHandlerFactory.cpp 
  src/EntityRequestHandlerFactory.h 
  src/PingHandler.cpp 
  src/PingHandler.h)

add_subdirectory(submodule/json)
include_directories(submodule/json/include)


add_executable(Server ${SOURCE_FILES})

add_subdirectory(submodule/poco)
include_directories(submodule/poco/Util/include)
include_directories(submodule/poco/Foundation/include)
include_directories(submodule/poco/Net/include)

# find_library(POCO_FOUNDATION PocoFoundation)
# find_library(POCO_UTIL PocoUtil)
# find_library(POCO_NET PocoNet)
target_link_libraries(Server Foundation Util Net)

