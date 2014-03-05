#ifndef INITGAME_H_
#define INITGAME_H_

#include <string>
#include <vector>
#include "Json/IJsonSerializable.h"
#include "Json/JsonTypes.h"
#include "Common/Vector.h"
#include "Common/Player.h"
#include "Common/GameType.h"

namespace json
{
class InitGame: public IJsonSerializable
{
public:
    InitGame();
    InitGame(int gameID, Vector map, const std::vector<Player> &players,
            GameType type);
    virtual ~InitGame() noexcept (true);
    virtual bool serialize(Json::Value& root);
    virtual bool deserialize(Json::Value& root);

    int getGameId() const;
    Vector getMapVector() const;
    void getPlayers(std::vector<Player>& players);
    GameType getGameType() const;

private:
    int m_gameId;
    Vector m_mapVector;
    std::vector<Player> m_players;
    GameType m_gameType;
    static std::string type;
};
}

#endif /* INITGAME_H_ */
