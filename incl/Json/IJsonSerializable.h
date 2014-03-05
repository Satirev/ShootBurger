#ifndef IJSONSERIALIZABLE_H_
#define IJSONSERIALIZABLE_H_

#include <json/json.h>

namespace json
{
class IJsonSerializable
{
public:
    virtual ~IJsonSerializable() = default;
    virtual bool serialize(Json::Value& root) = 0;
    virtual bool deserialize(Json::Value& root) = 0;
};
}

#endif /* IJSONSERIALIZABLE_H_ */
