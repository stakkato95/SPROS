cmake_minimum_required(VERSION 3.16)
project(WebSocketTest)

set(CMAKE_CXX_STANDARD 17)

# POCO
set(Poco_INCLUDE_DIRS /usr/local/include/Poco)
set(Poco_LIBRARIES Poco::Foundation Poco::Net)
find_package(Poco REQUIRED COMPONENTS Foundation XML Net Util JSON)
include_directories(${Poco_INCLUDE_DIRS})

# Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_LIBRARIES Boost::filesystem Boost::regex)
find_package(Boost COMPONENTS system)

add_executable(${PROJECT_NAME} main.cpp
        helper/Helper.h
        helper/MessageTypeConst.h
        model/request/Position.h
        model/request/ShowUp.h
        model/request/Position.h
        model/request/Model.h
        model/request/StartSessionAck.h
        model/request/PingAck.h
        model/response/Registration.h
        model/response/StartSession.h
        model/response/StartAction.h
        model/response/Ping.h
        transport/Message.cpp transport/Message.h
        net/SocketWrapper.cpp net/SocketWrapper.h
        net/adapter/MessageFactory.h
        net/adapter/MessageAdapter.h
        net/adapter/RegistrationAdapter.h
        net/adapter/DroneInfoAdapter.h
        net/adapter/StartSessionAdapter.h
        net/adapter/StartActionAdapter.h
        net/adapter/PingAdapter.h
        controller/DroneNetwork.cpp controller/DroneNetwork.h
        controller/NetworkResponder.h
        NetworkController.cpp NetworkController.h model/request/ActionFinished.h model/response/ShowUpAck.h net/adapter/ShowUpAckAdapter.h)

target_link_libraries(${PROJECT_NAME} ${Poco_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} stdc++fs)