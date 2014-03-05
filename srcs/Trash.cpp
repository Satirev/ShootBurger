#include "Automata/Trash.h"

Trash::Trash(Client *owner) :
                AState(owner)
{
}

Trash::~Trash()
{
}

AState *Trash::Process(const std::string &request)
{
    return 0;
}

AState *Trash::Process(JSON_NOTIFY type, std::string &answer,
        json::IJsonSerializable *obj)
{
    return 0;
}
