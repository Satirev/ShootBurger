#include "Json/HelloResponse.h"
using namespace json;

std::string HelloResponse::type = "HelloAnswer";

HelloResponse::HelloResponse()
{
}

HelloResponse::HelloResponse(Player player) :
                m_player(player)
{
}

HelloResponse::~HelloResponse() noexcept (true)
{
}

bool HelloResponse::serialize(Json::Value& root)
{
    root["type"] = HelloResponse::type;
    Json::Value value;
    value["player"]["name"] = m_player.name;
    value["player"]["color"] = m_player.color;
    root["data"] = value;
    return true;
}

bool HelloResponse::deserialize(Json::Value& root)
{
    if (!root.isMember("data"))
    {
        return false;
    }

    Json::Value data = root["data"];
    if (!data.isMember("player"))
    {
        return false;
    }

    m_player.name = data["player"].get("name", "").asString();
    m_player.color = data["player"].get("color", 0).asInt();

    return !m_player.name.empty();
}

Player HelloResponse::getPlayer() const
{
    return m_player;
}
