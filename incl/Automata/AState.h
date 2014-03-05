#ifndef ASTATE_H_
#define ASTATE_H_

#include <string>
#include <iostream>
#include "Json/JsonTypes.h"
#include "Json/IJsonSerializable.h"
#include "Common/Client.h"

enum AUTOMATA_STATE
{
    S_Uninitialized, S_Connected, S_InRoom, S_Playing, S_Trash
};

class AState
{
public:
    AState(Client *owner) :
                    t_next_state(0), t_next_state_id(S_Uninitialized),
                    t_owner(owner)
    {
    }
    virtual ~AState()
    {
    }

    virtual AState *Process(const std::string &request) = 0;
    virtual AState *Process(JSON_NOTIFY type, std::string &answer,
            json::IJsonSerializable *obj) = 0;

protected:
    AState *t_next_state;
    AUTOMATA_STATE t_next_state_id;
    Client *t_owner;
};

#endif /* ASTATE_H_ */
