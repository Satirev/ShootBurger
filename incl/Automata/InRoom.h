#ifndef INROOM_H_
#define INROOM_H_

#include <string>
#include "AState.h"

class InRoom: public AState
{
public:
    InRoom(Client *owner);
    virtual ~InRoom();

    AState *Process(const std::string &request);
    AState *Process(JSON_NOTIFY type, std::string &answer,
            json::IJsonSerializable *obj);
};

#endif /* INROOM_H_ */
