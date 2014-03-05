#include "Json/JsonSerializer.h"
using namespace json;

bool JsonSerializer::serialize(IJsonSerializable* object, std::string& output)
{
    if (object == nullptr)
    {
        return false;
    }

    Json::Value root;
    object->serialize(root);
    Json::StyledWriter writer;
    output = writer.write(root);
    return true;
}

bool JsonSerializer::deserialize(IJsonSerializable* object,
        const std::string& input)
{
    if (object == nullptr)
    {
        return false;
    }

    Json::Value root;
    Json::Reader reader;

    if (!reader.parse(input, root))
    {
        return false;
    }


    return object->deserialize(root);
}
