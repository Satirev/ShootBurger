#ifndef PLAYING_H_
#define PLAYING_H_

#include <string>
#include "AState.h"

class Playing: public AState
{
public:
    Playing(Client *owner);
    virtual ~Playing();

    AState *Process(const std::string &request);
    AState *Process(JSON_NOTIFY type, std::string &answer,
            json::IJsonSerializable *obj);
};

#endif /* PLAYING_H_ */
