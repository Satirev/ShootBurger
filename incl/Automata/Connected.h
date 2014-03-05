#ifndef CONNECTED_H_
#define CONNECTED_H_

#include <string>
#include "AState.h"

class Connected: public AState
{
public:
    Connected(Client *owner);
    virtual ~Connected();

    AState *Process(const std::string &request);
    AState *Process(JSON_NOTIFY type, std::string &answer,
            json::IJsonSerializable *obj);
};

#endif /* CONNECTED_H_ */
