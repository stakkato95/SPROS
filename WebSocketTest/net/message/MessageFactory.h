//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_MESSAGEFACTORY_H
#define WEBSOCKETTEST_MESSAGEFACTORY_H

#include <unordered_map>
#include <typeindex>

#include "MessageAdapter.h"

class MessageFactory {
public:
    MessageFactory() = default;

    void registerAdapter(IMessageAdapter *adapter, std::string &&type) {
        adapters[type] = adapter;
    }

    template<typename T>
    T parseJson(Poco::JSON::Object::Ptr &obj, std::string&& type) {
        const MessageAdapter<T> *adapter = static_cast<MessageAdapter<T> *>(adapters.at(type));
        return adapter->getModel(obj);
    }

private:
    std::unordered_map<std::string, IMessageAdapter*> adapters;
};


#endif //WEBSOCKETTEST_MESSAGEFACTORY_H
