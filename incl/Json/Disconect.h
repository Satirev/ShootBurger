#ifndef DISCONECT_H_
#define DISCONECT_H_

#include <string>
#include "Json/IJsonSerializable.h"

namespace json
{
class Disconect: public IJsonSerializable
{
public:
    Disconect();
    virtual ~Disconect();
    bool serialize(Json::Value& root);
    bool deserialize(Json::Value& root);

private:
    static std::string type;
};
}

#endif /* DISCONECT_H_ */
