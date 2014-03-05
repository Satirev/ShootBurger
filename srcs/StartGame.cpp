#include "Json/StartGame.h"
using namespace json;

std::string StartGame::type = "StartGame";

StartGame::StartGame(unsigned int delay) :
                m_delay(delay)
{

}

StartGame::~StartGame() noexcept (true)
{
}

bool StartGame::serialize(Json::Value& root)
{
    root["type"] = StartGame::type;
    root["data"]["delay"] = m_delay;
    return true;
}

bool StartGame::deserialize(Json::Value& root)
{
    bool result = false;
    if (root.isMember("data"))
    {
        Json::Value data = root["data"];
        if (data != 0)
        {
            m_delay = data.get("delay", "").asInt();
            result = true;
        }
    }
    return result;
}

void StartGame::SetDelay(unsigned int delay)
{
    m_delay = delay;
}

unsigned int StartGame::GetDelay() const
{
    return m_delay;
}
