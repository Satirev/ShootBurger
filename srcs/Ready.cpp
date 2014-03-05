#include "Json/Ready.h"
using namespace json;

std::string Ready::type = "Ready";

Ready::Ready() :
                m_status(0)
{
}

Ready::~Ready() noexcept (true)
{
}

bool Ready::serialize(Json::Value& root)
{
    root["type"] = Ready::type;
    root["data"]["status"] = m_status;
    return true;
}

bool Ready::deserialize(Json::Value& root)
{
    if (!root.isMember("data"))
    {
        return false;
    }

    Json::Value data = root["data"];

    if (!data.isMember("status"))
    {
        return false;
    }

    m_status = data.get("status", 0).asInt();
    return true;
}

bool Ready::getStatus() const
{
    return static_cast<bool>(m_status);
}
