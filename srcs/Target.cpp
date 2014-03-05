#include "Json/Target.h"
using namespace json;

std::string Target::type = "Target";

Target::Target() :
                m_type(CREATE), m_id(-1)
{
}

Target::Target(Vector pos, TargetType type, int id) :
                m_position(pos), m_type(type), m_id(id)
{
}

Target::~Target() noexcept (true)
{
}

bool Target::serialize(Json::Value& root)
{
    if (m_id == -1)
    {
        return false;
    }

    root["type"] = Target::type;
    root["data"]["type"] = m_type;
    root["data"]["id"] = m_id;
    root["data"]["position"]["x"] = m_position.x;
    root["data"]["position"]["y"] = m_position.y;
    root["data"]["position"]["z"] = m_position.z;
    return true;
}

bool Target::deserialize(Json::Value& root)
{
    // Taget will be sent from Server to Client, so deserialization is not required
    return false;
}

void Target::setPosition(const Vector& newPosition)
{
    m_position = newPosition;
}

void Target::setTargetType(const TargetType type)
{
    m_type = type;
}

void Target::setId(int id)
{
    m_id = id;
}

Vector Target::getPosition() const
{
    return m_position;
}

int Target::getId() const
{
    return m_id;
}

TargetType Target::getType() const
{
    return m_type;
}
