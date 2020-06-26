cmake_minimum_required(VERSION 3.16)
project(MQTTClient)

set(CMAKE_CXX_STANDARD 17)

# Paho MQTT
find_package(OpenSSL REQUIRED)
find_library(paho-mqttpp3 NAMES libpaho-mqttpp3.so REQUIRED)
find_library(paho-mqtt3a NAMES libpaho-mqtt3a.so REQUIRED)
# Paho MQTT
add_library(pahottpp STATIC IMPORTED)
set_target_properties(pahottpp PROPERTIES IMPORTED_LOCATION ${paho-mqttpp3})
# Paho MQTT
add_library(pahomqtt3a SHARED IMPORTED)
set_property(TARGET pahomqtt3a PROPERTY IMPORTED_LOCATION ${paho-mqtt3a})

# Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_LIBRARIES Boost::filesystem Boost::regex)
find_package(Boost COMPONENTS system)

add_executable(${PROJECT_NAME} main.cpp message/Message.h message/GNSSMessage.h helper/Helper.h)

target_link_libraries(${PROJECT_NAME} pahottpp)
target_link_libraries(${PROJECT_NAME} pahomqtt3a)
target_link_libraries(${PROJECT_NAME} ${Poco_LIBRARIES} ${Boost_LIBRARIES})