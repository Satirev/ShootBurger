#ifndef SERVERCONFIG_H_
#define SERVERCONFIG_H_

#include <string>
#include <websocketpp/config/asio_no_tls.hpp>

struct ServerConfig: public websocketpp::config::asio
{
    struct ConnectionData
    {
        uint64_t sessionId;
        std::string name;
    };

    typedef websocketpp::config::asio core;
    typedef core::concurrency_type concurrency_type;
    typedef core::request_type request_type;
    typedef core::response_type response_type;
    typedef core::message_type message_type;
    typedef core::con_msg_manager_type con_msg_manager_type;
    typedef core::endpoint_msg_manager_type endpoint_msg_manager_type;
    typedef core::alog_type alog_type;
    typedef core::elog_type elog_type;
    typedef core::rng_type rng_type;
    typedef core::transport_type transport_type;
    typedef ConnectionData connection_base;
};

#endif /* SERVERCONFIG_H_ */
