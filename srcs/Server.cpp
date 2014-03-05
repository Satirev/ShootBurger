#include "WebSocket/Server.h"
#include "Defines-Debugers.h"

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;
using websocketpp::lib::ref;

uint64_t Server::NextSessionId = 1;

Server::Server(boost::asio::ip::address ip, uint16_t port) :
                m_address(ip), m_port(port),
                m_sender(&Server::sendMessages, this), m_exit(false)
{
}

Server::~Server()
{
}

bool Server::init()
{
    try
    {
        m_server.set_access_channels(websocketpp::log::alevel::none);
        m_server.clear_access_channels(websocketpp::log::alevel::none);
        m_server.init_asio();
        m_server.set_open_handler(bind(&Server::onOpen, this, ::_1));
        m_server.set_close_handler(bind(&Server::onClose, this, ::_1));
        m_server.set_message_handler(
                bind(&Server::onMessage, this, ::_1, ::_2));
        return true;
    } catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    } catch (websocketpp::lib::error_code &e)
    {
        std::cout << e.message() << std::endl;
    } catch (...)
    {
        std::cout << "Unknow exception" << std::endl;
    }

    return false;
}

void Server::Task()
{
    if (init())
    {
        try
        {
            m_server.listen(m_address, m_port);
            m_server.start_accept();
            m_server.run();
        } catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
        } catch (websocketpp::lib::error_code &e)
        {
            std::cout << e.message() << std::endl;
        } catch (...)
        {
            std::cout << "Unknow exception" << std::endl;
        }
    }
}

void Server::Stop()
{
    m_exit = true;
    m_sender.join();
    m_server.stop();
    m_server.stop_listening();
}

void Server::onOpen(connection_hdl hdl)
{
    server::connection_ptr connection = m_server.get_con_from_hdl(hdl);
    connection->sessionId = Server::NextSessionId++;
    connection->name = "client" + std::to_string(connection->sessionId);
    std::cout << "New connection from: " << connection->name << std::endl;
    m_connections.insert(hdl);

}

void Server::onClose(connection_hdl hdl)
{
    server::connection_ptr connection = m_server.get_con_from_hdl(hdl);
    std::cout << "Closed connection by: " << connection->name << std::endl;
    std::string client = connection->name;
    std::string message = "{ \"type\" : \"Disconected\" }";
    WebSocketConnector::pushInputQueue(std::make_pair(client, message));
    m_connections.erase(hdl);
}

void Server::onMessage(connection_hdl hdl, server::message_ptr msg)
{
    server::connection_ptr connection = m_server.get_con_from_hdl(hdl);
//    std::cout << "Message from: " << connection->name << std::endl;
    std::string sender = connection->name.c_str();
    std::string message = msg->get_raw_payload();
    WebSocketConnector::pushInputQueue(std::make_pair(sender, message));
}

void Server::sendMessages()
{
    while (!m_exit)
    {
        usleep(500);
        std::pair<std::string, std::string> message =
                WebSocketConnector::popOutputQueue();
        if (message.first != "" && message.second != "")
        {
#ifdef JSON_MESSAGE
            std::cout << "[SERVER.CPP] " << message.first << " # " << message.second << std::endl;
#endif
            std::string clientConnectionName = message.first;
            for (auto& it : m_connections)
            {
                server::connection_ptr connection = m_server.get_con_from_hdl(
                        it);
                std::string currentConnectionName = connection->name;
                if (currentConnectionName == clientConnectionName)
                {
                    m_server.send(it, message.second,
                            websocketpp::frame::opcode::text);
                    break;
                }
            }
        }
    }
}

