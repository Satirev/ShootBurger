#include "Json/Shot.h"
using namespace json;

std::string Shot::type = "Shot";

Shot::Shot()
{
}

Shot::~Shot() noexcept (true)
{
}

bool Shot::serialize(Json::Value& root)
{
    root["type"] = Shot::type;
    root["data"]["vec"]["x"] = m_shotVector.x;
    root["data"]["vec"]["y"] = m_shotVector.y;
    root["data"]["vec"]["z"] = m_shotVector.z;
    root["data"]["power"] = m_power;
    return true;
}

bool Shot::deserialize(Json::Value& root)
{
    if (!root.isMember("data"))
    {
        return false;
    }

    Json::Value data = root["data"];
    if (!data.isMember("vec"))
    {
        return false;
    }

    Vector vector;
    vector.x = data["vec"].get("x", 0).asInt();
    vector.y = data["vec"].get("y", 0).asInt();
    vector.z = data["vec"].get("z", 0).asInt();
    m_shotVector = vector;
    m_power = data["power"].asInt();
    return true;
}

void Shot::setShotVector(const Vector& vector)
{
    m_shotVector = vector;
}

Vector Shot::getShotVector() const
{
    return m_shotVector;
}

void Shot::setPower(int power)
{
    m_power = power;
}

int Shot::getPower() const
{
    return m_power;
}
