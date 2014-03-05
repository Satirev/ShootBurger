#ifndef MAP_H_
#define MAP_H_

#include <map>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Common/Client.h"

class Map
{
public:
    Map()
    {
    }
    ~Map()
    {
        for (auto item = m_map.begin(); item != m_map.end(); ++item)
        {
            delete (*item).second;
        }
    }

    void Insert(const std::string &id, Client *client)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_map.insert(
        { id, client });
        lock.unlock();
    }

    Client *Find(const std::string &id)
    {
        Client *result = 0;
        std::unique_lock<std::mutex> lock(m_mutex);
        if (!m_map.empty())
        {
            auto pos = m_map.find(id);
            if (pos != m_map.end())
            {
                result = (*pos).second;
            }
        }
        lock.unlock();
        return result;
    }

    const std::string FindKey(Client *client)
    {
        std::string result = "";
        std::unique_lock<std::mutex> lock(m_mutex);
        if (!m_map.empty())
        {
            for (auto item : m_map)
            {
                if (item.second == client)
                {
                    result = item.first;
                    break;
                }
            }
        }
        lock.unlock();
        return result;
    }

private:
    std::map<std::string, Client*> m_map;
    std::mutex m_mutex;
    std::condition_variable m_cond;
};

#endif /* MAP_H_ */
