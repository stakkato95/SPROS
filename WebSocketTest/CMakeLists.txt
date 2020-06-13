cmake_minimum_required(VERSION 3.16)
project(WebSocketTest)

set(CMAKE_CXX_STANDARD 17)

find_package(Poco REQUIRED COMPONENTS Foundation XML Net Util JSON)
set(POCO_INCLUDE_DIRS /usr/local/include/Poco)
set(POCO_LIBRARIES Poco::Foundation Poco::Net)

include_directories(${POCO_INCLUDE_DIRS})

add_executable(WebSocketTest main.cpp)

target_link_libraries(WebSocketTest ${POCO_LIBRARIES})