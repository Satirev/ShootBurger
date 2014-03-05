#include "Common/Dispatcher.h"
#include "Common/Map.h"
#include "Common/Worker.h"
#include "WebSocket/WebSocketConnector.h"

Dispatcher::Dispatcher(unsigned int workersAmount, Lobby *lobby) :
                m_workers_amount(workersAmount), m_lobby(lobby)
{
    m_clients = new Map();
    m_workers.reserve(m_workers_amount);
    for (unsigned int num = 0; num < m_workers_amount; ++num)
    {
        m_workers.push_back(new Worker(m_clients, m_lobby, this));
    }
}

Dispatcher::~Dispatcher()
{
    for (auto worker = m_workers.begin(); worker != m_workers.end(); ++worker)
    {
        (*worker)->Halt();
        (*worker)->Wait();
        delete (*worker);
    }
    delete m_clients;
}

void Dispatcher::RunWorkers()
{
    for (auto worker : m_workers)
    {
        worker->Run();
    }
}

void Dispatcher::PushOut(Client* client, const std::string &message)
{
    WebSocketConnector::pushOutputQueue(
    { m_clients->FindKey(client), message });
}
