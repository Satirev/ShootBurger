#include "Json/Disconect.h"
using namespace json;

std::string Disconect::type = "Disconected";

Disconect::Disconect()
{
}

Disconect::~Disconect()
{
}

bool Disconect::serialize(Json::Value& root)
{
    root["type"] = type;
    return true;
}

bool Disconect::deserialize(Json::Value& root)
{
    return root["type"] == type;
}
