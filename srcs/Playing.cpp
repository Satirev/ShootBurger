#include "Automata/Playing.h"
#include "Automata/InRoom.h"
#include "Automata/Trash.h"
#include "Automata/Uninitialized.h"
#include "Json/JsonSerializer.h"
#include "Json/Shot.h"
#include "Json/Disconect.h"
#include "Lobby.h"

Playing::Playing(Client *owner) :
                AState(owner)
{
}

Playing::~Playing()
{
}

AState *Playing::Process(const std::string &request)
{
    t_next_state = 0;
    t_next_state_id = S_Uninitialized;
    json::Shot shoot_request;
    json::Disconect disc;
    if (json::JsonSerializer::deserialize(&shoot_request, request))
    {
        t_next_state_id = S_Playing;
    }
    else if (json::JsonSerializer::deserialize(&disc, request))
    {
        t_next_state_id = S_Trash;
    }

    switch (t_next_state_id)
    {
    case S_Playing:
        std::cout << "Playing -> Playing" << std::endl;
        t_owner->GetLobby()->shoot(t_owner, shoot_request.getShotVector());
        t_next_state = new Playing(t_owner);
        break;
    case S_Trash:
        std::cout << "Uninitialized -> Trash" << std::endl;
        t_owner->GetLobby()->leave(t_owner);
        t_next_state = new Trash(t_owner);
        break;
    default:
        std::cout << "Playing -> Playing (error)" << std::endl;
    }
    return t_next_state;
}

AState *Playing::Process(JSON_NOTIFY type, std::string &answer,
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
