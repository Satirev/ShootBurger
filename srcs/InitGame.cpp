#include "Json/InitGame.h"
using namespace json;

std::string InitGame::type = "InitGame";

InitGame::InitGame() :
                m_gameId(0)
{
}

InitGame::InitGame(int gameID, Vector map, const std::vector<Player> &players,
        GameType type) :
                m_gameId(gameID), m_mapVector(map), m_gameType(type)
{
    m_players.reserve(players.size());
    for (auto player : players)
    {
        m_players.push_back(player);
    }
}

InitGame::~InitGame() noexcept (true)
{
}

bool InitGame::serialize(Json::Value& root)
{
    root["type"] = InitGame::type;
    root["data"]["gameID"] = m_gameId;
    root["data"]["map"]["x"] = m_mapVector.x;
    root["data"]["map"]["y"] = m_mapVector.y;
    root["data"]["map"]["z"] = m_mapVector.z;

    for (unsigned int i = 0; i < m_players.size(); i++)
    {
        Json::Value value;
        value["name"] = m_players[i].name;
        value["color"] = m_players[i].color;
        root["data"]["players"].append(value);
    }

    root["data"]["gameType"]["id"] = m_gameType.id;
    root["data"]["gameType"]["value"] = m_gameType.value;
    return true;
}

bool InitGame::deserialize(Json::Value& root)
{
    if (!root.isMember("data"))
    {
        return false;
    }

    Json::Value data = root["data"];

    m_gameId = data.get("gameID", "").asInt();
    Json::Value map = data["map"];
    m_mapVector.x = map.get("x", 0).asInt();
    m_mapVector.y = map.get("y", 0).asInt();
    m_mapVector.z = map.get("z", 0).asInt();

    m_players.clear();
    Json::Value players = data["players"];
    for (unsigned int i = 0; i < players.size(); i++)
    {
        Player player;
        player.name = players[i]["name"].asString();
        player.color = players[i]["color"].asInt();
        m_players.push_back(player);
    }

    GameType gameType;
    gameType.id = data["gameType"]["id"].asInt();
    gameType.value = data["gameType"]["value"].asInt();
    m_gameType = gameType;
    return true;
}

int InitGame::getGameId() const
{
    return m_gameId;
}

Vector InitGame::getMapVector() const
{
    return m_mapVector;
}

void InitGame::getPlayers(std::vector<Player>& players)
{
    players.clear();
    players.insert(players.begin(), m_players.begin(), m_players.end());
}

GameType InitGame::getGameType() const
{
    return m_gameType;
}
