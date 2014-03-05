#ifndef TARGET_H_
#define TARGET_H_

#include <string>
#include "Json/IJsonSerializable.h"
#include "Common/Vector.h"
#include "Json/JsonTypes.h"

namespace json
{
class Target: public IJsonSerializable
{
public:
    Target();
    Target(Vector pos, TargetType type, int id);
    virtual ~Target() noexcept (true);
    virtual bool serialize(Json::Value& root);
    virtual bool deserialize(Json::Value& root);

    void setPosition(const Vector& newPosition);
    void setTargetType(const TargetType type);
    void setId(int id);
    Vector getPosition() const;
    int getId() const;
    TargetType getType() const;

private:
    Vector m_position;
    TargetType m_type;
    int m_id;
    static std::string type;
};
}

#endif /* TARGET_H_ */
