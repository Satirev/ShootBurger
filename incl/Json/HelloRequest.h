#ifndef HELLOREQUEST_H_
#define HELLOREQUEST_H_

#include <string>
#include "Json/IJsonSerializable.h"

namespace json
{
class HelloRequest: public IJsonSerializable
{
public:
    HelloRequest();
    HelloRequest(const std::string &name);
    virtual ~HelloRequest() noexcept (true);
    virtual bool serialize(Json::Value& root);
    virtual bool deserialize(Json::Value& root);

    const std::string& getName() const;

private:
    std::string m_name;
    static std::string type;
};
}

#endif /* HELLOREQUEST_H_ */
