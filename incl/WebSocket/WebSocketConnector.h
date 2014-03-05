#ifndef WEBSOCKETCONNECTOR_H_
#define WEBSOCKETCONNECTOR_H_

#include <utility>
#include <string>
#include "Common/Queue.h"
#include <boost/utility.hpp>

class WebSocketConnector: boost::noncopyable
{
public:
    WebSocketConnector() = delete;
    static void pushInputQueue(std::pair<std::string, std::string> message);
    static std::pair<std::string, std::string> popInputQueue();
    static void pushOutputQueue(std::pair<std::string, std::string> message);
    static std::pair<std::string, std::string> popOutputQueue();

private:
    static Queue<std::pair<std::string, std::string> > inputQueue;
    static Queue<std::pair<std::string, std::string> > outputQueue;
};

#endif /* WEBSOCKETCONNECTOR_H_ */
