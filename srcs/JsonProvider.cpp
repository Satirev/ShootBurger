#include "Json/JsonProvider.h"
#include "Json/IJsonSerializable.h"
#include "Json/HelloResponse.h"
#include "Json/InitGame.h"
#include "Json/StartGame.h"
#include "Json/EndGame.h"
#include "Json/Interval.h"
#include "Json/Target.h"
#include "Json/Score.h"
using namespace json;

JsonProvider::JsonProvider()
{
}

JsonProvider::~JsonProvider()
{
}

IJsonSerializable *JsonProvider::MakeHelloRespone(const Player &player)
{
    return new HelloResponse(player);
}

IJsonSerializable *JsonProvider::MakeInitGame(int gameID, const Vector &map,
        const std::vector<Player> &players, const GameType &type)
{
    return new InitGame(gameID, map, players, type);
}

IJsonSerializable *JsonProvider::MakeStartGame(unsigned int delay)
{
    return new StartGame(delay);
}

IJsonSerializable *JsonProvider::MakeEndGame(const std::string &playerName,
        int score)
{
    return new EndGame(playerName, score);
}

IJsonSerializable *JsonProvider::MakeInterval(int time,
        const std::vector<Ball> &balls)
{
    return new Interval(time, balls);
}

IJsonSerializable *JsonProvider::MakeTarget(const Vector &pos, TargetType type,
        int id)
{
    return new Target(pos, type, id);
}

IJsonSerializable *JsonProvider::MakeScore(const std::string &playerName,
        int score)
{
    return new Score(playerName, score);
}
