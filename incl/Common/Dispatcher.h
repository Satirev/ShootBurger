#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include <vector>
#include <string>
class Map;
class Worker;
class Client;
class Lobby;

class Dispatcher
{
public:
    Dispatcher(unsigned int workersAmount, Lobby *lobby);
    virtual ~Dispatcher();

    void RunWorkers();
    void PushOut(Client* client, const std::string &message);

private:
    unsigned int m_workers_amount;
    std::vector<Worker*> m_workers;
    Map *m_clients;
    Lobby *m_lobby;
};

#endif /* DISPATCHER_H_ */
