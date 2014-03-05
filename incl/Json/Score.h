#ifndef SCORE_H_
#define SCORE_H_

#include <string>
#include "Json/IJsonSerializable.h"

namespace json
{
class Score: public IJsonSerializable
{
public:
    Score();
    Score(const std::string& playerName, int score);
    virtual ~Score() noexcept (true);
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

#endif /* SCORE_H_ */
