#include "Json/HelloRequest.h"
using namespace json;

std::string HelloRequest::type = "HelloRequest";

HelloRequest::HelloRequest()
{
}

HelloRequest::HelloRequest(const std::string &name) :
                m_name(name)
{
}

HelloRequest::~HelloRequest() noexcept (true)
{
}

bool HelloRequest::serialize(Json::Value& root)
{
    if (m_name.empty())
    {
        return false;
    }
    root["type"] = HelloRequest::type;
    Json::Value value;
    value["name"] = m_name;
    root["data"] = value;
    return true;
}

bool HelloRequest::deserialize(Json::Value& root)
{
    if (!root.isMember("data"))
    {
        return false;
    }

    Json::Value value = root["data"];
    m_name = value.get("name", "").asString();
    return !m_name.empty();
}

const std::string& HelloRequest::getName() const
{
    return m_name;
}
