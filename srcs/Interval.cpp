#include "Json/Interval.h"
using namespace json;

std::string Interval::type = "Interval";

Interval::Interval() :
                m_time(0)
{
}

Interval::Interval(int time, const std::vector<Ball>& balls) :
                m_time(time)
{
    m_balls.insert(m_balls.begin(), balls.begin(), balls.end());
}

Interval::~Interval() noexcept (true)
{
}

bool Interval::serialize(Json::Value& root)
{
    root["type"] = Interval::type;
    root["data"]["time"] = m_time;
    for (unsigned int i = 0; i < m_balls.size(); i++)
    {
        Json::Value value;
        Position currentPosition = m_balls[i].getCurrentPosition();
        value["position"]["x"] = currentPosition.x;
        value["position"]["y"] = currentPosition.y;
        value["position"]["z"] = currentPosition.z;
        value["color"] = m_balls[i].getColour();
        value["type"] = m_balls[i].getType();
        value["id"] = m_balls[i].getId();
        root["data"]["balls"].append(value);
    }
    return true;
}

bool Interval::deserialize(Json::Value& root)
{
    // Interval will be sent from Server to Cliend, so deserialization is not required
    return false;
}

void Interval::setTime(unsigned long time)
{
    m_time = time;
}

unsigned long Interval::getTime() const
{
    return m_time;
}

void Interval::setBalls(std::vector<Ball>& balls)
{
    m_balls.clear();
    m_balls.insert(m_balls.begin(), balls.begin(), balls.begin());
}

const std::vector<Ball>& Interval::getBalls() const
{
    return m_balls;
}
