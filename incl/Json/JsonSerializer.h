#ifndef JSONSERIALIZER_H_
#define JSONSERIALIZER_H_

#include <string>
#include "Json/IJsonSerializable.h"

namespace json
{
class JsonSerializer
{
public:
    JsonSerializer() = delete;
    JsonSerializer(const JsonSerializer&) = delete;

    static bool serialize(IJsonSerializable* object, std::string& output);
    static bool deserialize(IJsonSerializable* object,
            const std::string& input);
};
}

#endif /* JSONSERIALIZER_H_ */
