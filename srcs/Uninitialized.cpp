#include "Automata/Uninitialized.h"
#include "Automata/Connected.h"
#include "Automata/Trash.h"
#include "Json/JsonSerializer.h"
#include "Json/HelloRequest.h"
#include "Json/Disconect.h"
#include "Lobby.h"

Uninitialized::Uninitialized(Client *owner) :
                AState(owner)
{
}

Uninitialized::~Uninitialized()
{
}

AState *Uninitialized::Process(const std::string &request)
{
    t_next_state = 0;
    t_next_state_id = S_Uninitialized;
    json::HelloRequest hello_request;
    json::Disconect disc;
    if (json::JsonSerializer::deserialize(&hello_request, request))
    {
        t_next_state_id = S_Connected;
    }
    else if (json::JsonSerializer::deserialize(&disc, request))
    {
        t_next_state_id = S_Trash;
    }
    std::string tmp = "Room 1";
    std::string name = hello_request.getName();
    switch (t_next_state_id)
    {
    case S_Connected:
        std::cout << "Uninitialized -> Connected" << std::endl;
        t_owner->GetLobby()->join(t_owner, tmp, name);
        t_next_state = new Connected(t_owner);
        break;
    case S_Trash:
        std::cout << "Uninitialized -> Trash" << std::endl;
        t_next_state = new Trash(t_owner);
        break;
    default:
        std::cout << "Uninitialized -> Uninitialized (error)" << std::endl;
    }

    return t_next_state;
}

AState *Uninitialized::Process(JSON_NOTIFY type, std::string &answer,
        json::IJsonSerializable *obj)
{
    AState *result = 0;
    if (type == END_GAME)
    {
        std::cout << "Playing -> Uninitialized" << std::endl;
        t_owner->GetLobby()->leave(t_owner);
        result = new Uninitialized(t_owner);
    }
    json::JsonSerializer::serialize(obj, answer);
    return result;
}
