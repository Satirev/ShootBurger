#include "Automata/InRoom.h"
#include "Automata/Playing.h"
#include "Automata/Uninitialized.h"
#include "Automata/Trash.h"
#include "Json/JsonSerializer.h"
#include "Json/Ready.h"
#include "Json/Disconect.h"
#include "Lobby.h"

InRoom::InRoom(Client *owner) :
                AState(owner)
{
}

InRoom::~InRoom()
{
}

AState *InRoom::Process(const std::string &request)
{
    t_next_state = 0;
    t_next_state_id = S_Uninitialized;
    json::Ready ready_request;
    json::Disconect disc;
    if (json::JsonSerializer::deserialize(&ready_request, request))
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
        std::cout << "InRoom -> Playing" << std::endl;
        t_owner->GetLobby()->toggleReady(t_owner);
        t_next_state = new Playing(t_owner);
        break;
    case S_Trash:
        std::cout << "Uninitialized -> Trash" << std::endl;
        t_owner->GetLobby()->leave(t_owner);
        t_next_state = new Trash(t_owner);
        break;
    default:
        std::cout << "InRoom -> InRoom (error)" << std::endl;
    }
    return t_next_state;
}

AState *InRoom::Process(JSON_NOTIFY type, std::string &answer,
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
