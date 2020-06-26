cmake_minimum_required(VERSION 3.16)
project(MQTTClient)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)
find_library(paho-mqttpp3 NAMES libpaho-mqttpp3.so REQUIRED)
find_library(paho-mqtt3a NAMES libpaho-mqtt3a.so REQUIRED)

add_library(pahottpp STATIC IMPORTED)
set_target_properties(pahottpp PROPERTIES IMPORTED_LOCATION ${paho-mqttpp3})

add_library(pahomqtt3a SHARED IMPORTED)
set_property(TARGET pahomqtt3a PROPERTY IMPORTED_LOCATION ${paho-mqtt3a})


add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} pahottpp)
target_link_libraries(${PROJECT_NAME} pahomqtt3a)