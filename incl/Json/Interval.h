#ifndef INTERVAL_H_
#define INTERVAL_H_

#include <utility>
#include <vector>
#include <string>
#include "Json/IJsonSerializable.h"
#include "Common/Vector.h"
#include "Common/Ball.h"

namespace json
{
class Interval: public IJsonSerializable
{
public:
    Interval();
    Interval(int time, const std::vector<Ball>& balls);
    virtual ~Interval() noexcept (true);
    virtual bool serialize(Json::Value& root);
    virtual bool deserialize(Json::Value& root);

    void setTime(unsigned long time);
    unsigned long getTime() const;
    void setBalls(std::vector<Ball>& balls);
    const std::vector<Ball>& getBalls() const;

private:
    int m_time;
    std::vector<Ball> m_balls;
    static std::string type;
};
}

#endif /* INTERVAL_H_ */
