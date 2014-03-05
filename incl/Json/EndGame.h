#ifndef GAMEEND_H_
#define GAMEEND_H_

#include <string>
#include "Json/IJsonSerializable.h"

namespace json
{
class EndGame: public IJsonSerializable
{
public:
    EndGame();
    EndGame(const std::string &playerName, int score);
    virtual ~EndGame() noexcept (true);
    virtual bool serialize(Json::Value& root);
    virtual bool deserialize(Json::Value& root);

    void setScore(int score);
    int getScore() const;
    void setPlayerName(const std::string& name);
    const std::string& getPlayerName() const;

private:
    std::string m_playerName;
    int m_score;
    static std::string type;
};
}

#endif /* GAMEEND_H_ */
