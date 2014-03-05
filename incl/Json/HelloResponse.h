#ifndef HELLORESPONSE_H_
#define HELLORESPONSE_H_

#include <string>
#include "Json/IJsonSerializable.h"
#include "Common/Player.h"

namespace json
{
class HelloResponse: public IJsonSerializable
{
public:
    HelloResponse();
    HelloResponse(Player player);
    virtual ~HelloResponse() noexcept (true);
    bool serialize(Json::Value& root);
    bool deserialize(Json::Value& root);

    Player getPlayer() const;

private:
    Player m_player;
    static std::string type;
};
}

#endif /* HELLORESPONSE_H_ */
