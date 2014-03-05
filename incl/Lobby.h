#ifndef LOBBY_H_
#define LOBBY_H_

#include <string>
#include <map>
#include "Room/GameRoom.h"

class Client;

class Lobby
{
public:
    Lobby();
    ~Lobby();
    bool join(Client * client, const std::string &roomName,
            std::string &playerName);
    void leave(Client * client);
    void toggleReady(const Client * client);
    void shoot(const Client * client, const Vector &moveVector);

    void open();
    void close();
private:
    Lobby(Lobby&);
    Lobby& operator=(Lobby&);

    bool isRoomRegistered(const std::string &name) const;
    void registerClientInRoom(Client * client, GameRoom* gr);
    void unregisterClient(Client * client);
    void registerRoom(std::string name, GameRoom *gr);

    std::map<std::string, GameRoom*> m_gameRoomsMap;
    std::map<const Client*, GameRoom*> m_clientRoomMap;
};

inline void Lobby::registerClientInRoom(Client * client, GameRoom* gr)
{
    m_clientRoomMap.insert(std::pair<Client*, GameRoom*>(client, gr));
}

inline void Lobby::unregisterClient(Client* client)
{
    m_clientRoomMap.erase(client);
}

inline void Lobby::registerRoom(std::string name, GameRoom *gr)
{
    m_gameRoomsMap.insert(std::pair<std::string, GameRoom*>(name, gr));
}

#endif /* LOBBY_H_ */
