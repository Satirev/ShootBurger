#include "Json/EndGame.h"
using namespace json;

std::string EndGame::type = "GameEnd";

EndGame::EndGame() :
                m_score(0)
{
}

EndGame::EndGame(const std::string &playerName, int score) :
                m_playerName(playerName), m_score(score)
{
}

EndGame::~EndGame() noexcept (true)
{
}

bool EndGame::serialize(Json::Value& root)
{
    if (m_playerName.empty())
    {
        return false;
    }

    root["type"] = EndGame::type;
    root["data"]["winner"] = m_playerName;
    root["data"]["score"] = m_score;
    return true;
}

bool EndGame::deserialize(Json::Value& root)
{
    // GameEnd will be sent from Server to Client, so deserialization is not required
    return false;
}

void EndGame::setScore(int score)
{
    m_score = score;
}

int EndGame::getScore() const
{
    return m_score;
}

void EndGame::setPlayerName(const std::string& name)
{
    m_playerName = name;
}

const std::string& EndGame::getPlayerName() const
{
    return m_playerName;
}
