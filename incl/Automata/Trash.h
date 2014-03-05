#ifndef TRASH_H_
#define TRASH_H_

#include <string>
#include "Automata/AState.h"

class Trash: public AState
{
public:
    Trash(Client *owner);
    virtual ~Trash();

    AState *Process(const std::string &request);
    AState *Process(JSON_NOTIFY type, std::string &answer,
            json::IJsonSerializable *obj);
};

#endif /* TRASH_H_ */
