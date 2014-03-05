#include "Json/Score.h"
using namespace json;

std::string Score::type = "Score";

Score::Score() :
                m_score(0)
{
}

Score::Score(const std::string& playerName, int score) :
                m_playerName(playerName), m_score(score)
{
}

Score::~Score() noexcept (true)
{
}

bool Score::serialize(Json::Value& root)
{
    if (m_playerName.empty())
    {
        return false;
    }

    root["type"] = Score::type;
    root["data"]["playerName"] = m_playerName;
    root["data"]["score"] = m_score;
    return true;
}

bool Score::deserialize(Json::Value& root)
{
    if (!root.isMember("data"))
    {
        return false;
    }

    Json::Value data = root["data"];

    if (!data.isMember("playerName") || !data.isMember("score"))
    {
        return false;
    }

    m_playerName = data["playerName"].asString();
    m_score = data["score"].asInt();
    return true;
}

void Score::setScore(int score)
{
    m_score = score;
}

int Score::getScore() const
{
    return m_score;
}

void Score::setPlayerName(const std::string& name)
{
    m_playerName = name;
}

const std::string& Score::getPlayerName() const
{
    return m_playerName;
}
