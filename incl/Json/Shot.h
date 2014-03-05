#ifndef SHOT_H_
#define SHOT_H_

#include "Json/IJsonSerializable.h"
#include "Common/Vector.h"
#include <string>

namespace json
{
class Shot: public IJsonSerializable
{
public:
    Shot();
    virtual ~Shot() noexcept (true);
    virtual bool serialize(Json::Value& root);
    virtual bool deserialize(Json::Value& root);

    void setShotVector(const Vector& vector);
    Vector getShotVector() const;
    void setPower(int power);
    int getPower() const;

private:
    int m_power;
    Vector m_shotVector;
    static std::string type;
};
}

#endif /* SHOT_H_ */
