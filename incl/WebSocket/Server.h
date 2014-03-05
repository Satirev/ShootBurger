#ifndef SERVER_H_
#define SERVER_H_

#include <memory>
#include <string>
#include <iostream>
#include <set>
#include <utility>
#include <thread>
#include <algorithm>
#include <boost/utility.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/message_buffer/message.hpp>
#include "Common/AThread.h"
#include "WebSocket/ServerConfig.h"
#include "WebSocket/WebSocketConnector.h"

typedef websocketpp::server<ServerConfig> server;

typedef server::message_ptr message_ptr;

class Server: boost::noncopyable, public AThread
{
public:
    Server(boost::asio::ip::address ip, uint16_t port);
    ~Server();
    void Task();
    void Stop();

private:
    bool init();
    void onOpen(websocketpp::connection_hdl hdl);
    void onClose(websocketpp::connection_hdl hdl);
    void onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg);
    void sendMessages();

private:
    typedef std::set<websocketpp::connection_hdl,
            std::owner_less<websocketpp::connection_hdl> > connectionList;

    server m_server;
    connectionList m_connections;
    boost::asio::ip::address m_address;
    uint16_t m_port;
    static uint64_t NextSessionId;
    std::thread m_sender;bool m_exit;
};

#endif /* SERVER_H_ */

