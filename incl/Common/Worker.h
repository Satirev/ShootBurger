#ifndef WORKER_H_
#define WORKER_H_

#include "Common/AThread.h"
class Map;
class Lobby;
class Dispatcher;

class Worker: public AThread
{
public:
    Worker(Map *clients, Lobby *lobby, Dispatcher *disp);
    virtual ~Worker();

    void Task();

private:
    Map *m_clients;
    Lobby *m_lobby;
    Dispatcher *m_disp;
};

#endif /* WORKER_H_ */
