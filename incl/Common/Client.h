#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include "Json/JsonTypes.h"
#include "Json/IJsonSerializable.h"

class AState;
class Lobby;
class Dispatcher;

class Client
{
public:
    Client(Lobby *lobby, Dispatcher *disp);
    virtual ~Client();

    void ProcessRequest(const std::string &request);
    void Notify(JSON_NOTIFY type, json::IJsonSerializable *obj);
    Lobby *GetLobby();

private:
    std::string m_name;
    AState *m_current_state;
    Lobby *m_lobby;
    Dispatcher *m_disp;
};

#endif /* CLIENT_H_ */
