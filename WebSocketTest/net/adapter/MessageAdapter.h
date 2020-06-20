//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_MESSAGEADAPTER_H
#define WEBSOCKETTEST_MESSAGEADAPTER_H

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/JSONException.h"

class IMessageAdapter {
};

template<typename T>
class MessageAdapter : public IMessageAdapter {
public:
    virtual T getModel(Poco::JSON::Object::Ptr&) const noexcept(false) = 0;
};


#endif //WEBSOCKETTEST_MESSAGEADAPTER_H
