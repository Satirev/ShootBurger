#include "Automata/Connected.h"
#include "Automata/InRoom.h"
#include "Automata/Trash.h"
#include "Automata/Uninitialized.h"
#include "Json/JsonSerializer.h"
#include "Json/Ready.h"
#include "Json/Disconect.h"
#include "Lobby.h"

Connected::Connected(Client *owner) :
                AState(owner)
{
}

Connected::~Connected()
{
}

AState *Connected::Process(const std::string &request)
{
    t_next_state = 0;
    t_next_state_id = S_Uninitialized;
    json::Ready ready_request;
    json::Disconect disc;
    if (json::JsonSerializer::deserialize(&ready_request, request))
    {
        t_next_state_id = S_InRoom;
    }
    else if (json::JsonSerializer::deserialize(&disc, request))
    {
        t_next_state_id = S_Trash;
    }
    switch (t_next_state_id)
    {
    case S_InRoom:
        std::cout << "Connected -> InRoom" << std::endl;
        t_owner->GetLobby()->toggleReady(t_owner);
        t_next_state = new InRoom(t_owner);
        break;
    case S_Trash:
        std::cout << "Connected -> Trash" << std::endl;
        t_owner->GetLobby()->leave(t_owner);
        t_next_state = new Trash(t_owner);
        break;
    default:
        std::cout << "Connected -> Connected (error)" << std::endl;
    }

    return t_next_state;
}

AState *Connected::Process(JSON_NOTIFY type, std::string &answer,
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
