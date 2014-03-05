#ifndef UNINITIALIZED_H_
#define UNINITIALIZED_H_

#include <string>
#include "AState.h"

class Uninitialized: public AState
{
public:
    Uninitialized(Client *owner);
    virtual ~Uninitialized();

    AState *Process(const std::string &request);
    AState *Process(JSON_NOTIFY type, std::string &answer,
            json::IJsonSerializable *obj);
};

#endif /* UNINITIALIZED_H_ */
