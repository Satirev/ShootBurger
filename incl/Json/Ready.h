#ifndef READY_H_
#define READY_H_

#include "Json/IJsonSerializable.h"

namespace json
{
class Ready: public IJsonSerializable
{
public:
    Ready();
    virtual ~Ready() noexcept (true);
    virtual bool serialize(Json::Value& root);
    virtual bool deserialize(Json::Value& root);

    bool getStatus() const;

private:
    int m_status;
    static std::string type;
};
}

#endif /* READY_H_ */
