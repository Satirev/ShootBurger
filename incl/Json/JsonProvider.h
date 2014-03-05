#ifndef JSONPROVIDER_H_
#define JSONPROVIDER_H_

#include <vector>
#include <string>
#include "Json/IJsonSerializable.h"
#include "Json/JsonTypes.h"
#include "Common/Vector.h"
#include "Common/Player.h"
#include "Common/GameType.h"
#include "Common/Ball.h"

class GameType;

namespace json
{
class JsonProvider
{
public:
    JsonProvider();
    virtual ~JsonProvider();

    static IJsonSerializable *MakeHelloRespone(const Player &player);
    static IJsonSerializable *MakeInitGame(int gameID, const Vector &map,
            const std::vector<Player> &players, const GameType &type);
    static IJsonSerializable *MakeStartGame(unsigned int delay);
    static IJsonSerializable *MakeEndGame(const std::string &playerName,
            int score);
    static IJsonSerializable *MakeInterval(int time,
            const std::vector<Ball> &balls);
    static IJsonSerializable *MakeTarget(const Vector &pos, TargetType type,
            int id);
    static IJsonSerializable *MakeScore(const std::string &playerName,
            int score);
};
}

#endif /* JSONPROVIDER_H_ */
