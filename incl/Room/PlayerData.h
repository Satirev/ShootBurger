#ifndef PLAYERDATA_H_
#define PLAYERDATA_H_

#include "Common/Vector.h"
#include "Common/Player.h"
#include "Common/Ball.h"
#include <string>
#include <vector>

#include <iostream>

class Client;

class PlayerData
{
public:
    explicit PlayerData(Client * client, int &ballColour,
            const std::string &name = "");
    void setMoveVector(const Vector &newVector);
    ~PlayerData();

    inline Vector getMoveVector();
    inline Client* getClient();
    bool isReady() const;
    void setReady(bool ready);
    Ball& getBall();
    int getScore() const;
    void updateScore(int value=1);
    const std::string getName() const;
    const Player getPlayerStruct() const;
    void clearScore();

private:
    Client* m_client;
    Ball m_ball;
    std::string m_name;
    bool m_ready;
    int m_score;
};

inline void PlayerData::setMoveVector(const Vector& newVector)
{
    m_ball.setMoveVector(newVector);
}

inline Client* PlayerData::getClient()
{
    return m_client;
}

inline bool PlayerData::isReady() const
{
    return m_ready;
}

inline void PlayerData::setReady(bool ready)
{
    m_ready = ready;
}

inline Ball& PlayerData::getBall()
{
    return m_ball;
}

inline void PlayerData::updateScore(int value)
{
    m_score += value;
}

inline int PlayerData::getScore() const
{
    return m_score;
}

inline const std::string PlayerData::getName() const
{
    return m_name;
}

inline const Player PlayerData::getPlayerStruct() const
{
    Player data =
    { m_name, m_ball.getColour() };
    return data;
}

inline void PlayerData::clearScore()
{
	m_score = 0;
}

#endif /* PLAYERDATA_H_ */
