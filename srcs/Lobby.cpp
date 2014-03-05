#include "Lobby.h"
#include "Room/GameRoom.h"

#include <string>
#include <map>


Lobby::Lobby()
{
    RoomConfigurator roomConfig;
    roomConfig.mapSize = Vector(8000, 1000, 25000);
    roomConfig.maxPlayers = 8;
    roomConfig.rules = STATIC_TARGET;
    roomConfig.type.id = 1;
    roomConfig.type.value = 1;
    std::string roomName = "Room 1";
    GameRoom * gr = new GameRoom(roomConfig, roomName);
    registerRoom(roomName, gr);
}

Lobby::~Lobby()
{
    for (auto &mapItem : m_gameRoomsMap)
    {
        delete (mapItem.second);
    }
}

bool Lobby::join(Client * client, const std::string &roomName,
        std::string &playerName)
{

    if (isRoomRegistered(roomName))
    {
        GameRoom * gr = m_gameRoomsMap.find(roomName)->second;
        if (gr->addPlayer(playerName, client))
        {
            registerClientInRoom(client, gr);
            return true;
        }
        else
        {
            return false; //failed to join room
        }
    }
    else
    {
        return false; //failed no such room in lobby
    }
}

void Lobby::leave(Client* client)
{
    GameRoom * gr = m_clientRoomMap.find(client)->second;
//    gr->removePlayer(client);
    unregisterClient(client);
}

bool Lobby::isRoomRegistered(const std::string &name) const
{

    auto roomInMapIdx = m_gameRoomsMap.find(name);

    if (roomInMapIdx != m_gameRoomsMap.end())
    {
        return true;
    }
    else
    {
        return false;
    }

}

void Lobby::open()
{
    for (auto &mapItem : m_gameRoomsMap)
    {
        (mapItem.second)->play();
    }
}

void Lobby::close()
{
    for (auto &mapItem : m_clientRoomMap)
    {
        mapItem.second->stop();
    }
}

void Lobby::toggleReady(const Client* client)
{
    GameRoom * gr = m_clientRoomMap.find(client)->second;
    gr->toggleReady(client);
}

void Lobby::shoot(const Client* client, const Vector& moveVector)
{
    if (!moveVector.getModulus())
    {
        return;
    }
    GameRoom * gr = m_clientRoomMap.find(client)->second;
    gr->shoot(client, moveVector);
}
