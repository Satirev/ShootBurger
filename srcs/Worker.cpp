#include "Common/Worker.h"
#include "Common/Map.h"
#include "Common/Client.h"
#include "WebSocket/WebSocketConnector.h"
#include <utility>
#include <string>
#include <iostream>

Worker::Worker(Map *clients, Lobby *lobby, Dispatcher * disp) :
                m_clients(clients), m_lobby(lobby), m_disp(disp)
{
}

Worker::~Worker()
{
}

void Worker::Task()
{
    while (true)
    {
        usleep(500);
        std::pair<std::string, std::string> query =
                WebSocketConnector::popInputQueue();
        if (query.first != "" && query.second != "")
        {
            Client *sender = m_clients->Find(query.first);
            if (sender == 0)
            {
                sender = new Client(m_lobby, m_disp);
                m_clients->Insert(query.first, sender);
            }
            sender->ProcessRequest(query.second);
        }
    }
}
