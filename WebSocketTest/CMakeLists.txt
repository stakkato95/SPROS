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

add_executable(WebSocketTest main.cpp
        model/Position.h
        helper/Helper.h
        model/DroneInfo.h
        model/Position.h
        model/Model.h
        model/Registration.h
        model/StartSession.h
        model/StartSessionAck.h
        transport/Message.cpp transport/Message.h
        net/SocketWrapper.cpp net/SocketWrapper.h
        helper/MessageTypeConst.h
        net/adapter/MessageFactory.h
        net/adapter/MessageAdapter.h
        net/adapter/RegistrationAdapter.h
        net/adapter/DroneInfoAdapter.h
        net/adapter/StartSessionAdapter.h
        controller/DroneNetwork.cpp controller/DroneNetwork.h
        controller/NetCallback.h
        NetworkController.cpp NetworkController.h)

target_link_libraries(WebSocketTest ${Poco_LIBRARIES} ${Boost_LIBRARIES})