#ifndef GAMEROOM_H_
#define GAMEROOM_H_

#include "Common/Vector.h"
#include "Common/AThread.h"
#include "PlayerData.h"
#include "RoomConfigurator.h"
#include <vector>
#include <string>
#include <mutex>

class ABallProvider;
class Game;

enum GLOBAL_ROOM_SETTINGS
{
    BALL_RADIUS = 50,
    TARGET_RADIUS = 50,
    MOVE_FOR_ONE_CALCULATION = 5,
    SINGLE_CALC_STEP = 20,
};

enum GameStatus
{
    STOPPED, PLAYING
};

class GameRoom: public AThread
{
public:
    explicit GameRoom(const RoomConfigurator &roomConfig,
            const std::string &name);
    GameRoom(const GameRoom& gm) = delete;
    void play();
    void stop();
    bool addPlayer(const std::string &name, Client * client);
    void removePlayer(Client * client);
    void toggleReady(const Client * client);
    void shoot(const Client * client, const Vector& vector);
    virtual ~GameRoom();

    GameStatus getGameStatus() const;
    const std::string& getRoomName() const;

private:
    bool isGameRoomReady();
    virtual void Task();
    void endGame();
    void waitForGameBegin();
    void initGame();
    void startGame(int startGameDelay);
    void unreadyPlayers();
    bool isPlayerInRoom(const std::string& name) const;
    std::string createPlayerName(const std::string &playerName) const;

    const RoomConfigurator ROOM_CONFIG;
    const std::string ROOM_NAME;
    std::vector<PlayerData> m_players;
    GameStatus m_gameStatus;
    ABallProvider * m_balls;
    Game * m_currentGame;
    std::mutex m_mutex;
};

inline GameStatus GameRoom::getGameStatus() const
{
    return m_gameStatus;
}

inline const std::string& GameRoom::getRoomName() const
{
    return ROOM_NAME;
}

#endif /* GAMEROOM_H_ */
