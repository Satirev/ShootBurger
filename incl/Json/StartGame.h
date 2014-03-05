#ifndef STARTGAME_H_
#define STARTGAME_H_

#include <string>
#include <vector>
#include "Json/IJsonSerializable.h"
#include "Common/Vector.h"
#include "Common/Player.h"

namespace json
{
class StartGame: public IJsonSerializable
{
public:
    StartGame(unsigned int delay = 0);
    virtual ~StartGame() noexcept (true);
    virtual bool serialize(Json::Value& root);
    virtual bool deserialize(Json::Value& root);

    void SetDelay(unsigned int delay);
    unsigned int GetDelay() const;

private:
    unsigned int m_delay;
    static std::string type;
};
}

#endif /* STARTGAME_H_ */
