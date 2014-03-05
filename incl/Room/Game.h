#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include <random>
#include <algorithm>
#include <memory>
#include <utility>
#include <ctime>
#include "Room/PlayerData.h"
#include "Room/Rules.h"
#include "Room/Engine.h"
#include "Room/GameData.h"
#include "Json/JsonTypes.h"
#include "Common/Client.h"
#include "Common/GameType.h"
#include "Json/JsonProvider.h"
#include "Json/IJsonSerializable.h"

class Game
{
public:
    Game(GameKind type, std::vector<PlayerData>& players, Rules rules,
            const Vector & mapSize);
    ~Game();
    void nextMove();
    bool isEndGame();
    EndGameData getWinner() const;

private:
    void makeMove(GameData& gameData);
    void notifyClients(const GameData& gameData);

private:
    std::vector<PlayerData>& m_players;
    Rules m_rules;
    Engine m_engine;
    GameKind m_type;
    const time_t m_startTime;
    time_t m_currentTime;
    const time_t m_gameTotalTime;
    int m_gameTotalHits;
};

#endif /* GAME_H_ */
