//
// Created by artsiom on 13.06.20.
//

#include "RegistrationAdapter.h"

using namespace Poco::JSON;
using namespace std;

Registration RegistrationAdapter::getModel(Object::Ptr &json) const noexcept(false) {
    Registration r;

    r.id = json->getValue<string>("id");

    return r;
}
