#include "WebSocket/WebSocketConnector.h"

Queue<std::pair<std::string, std::string>> WebSocketConnector::inputQueue;
Queue<std::pair<std::string, std::string>> WebSocketConnector::outputQueue;

void WebSocketConnector::pushInputQueue(
        std::pair<std::string, std::string> message)
{
    inputQueue.push(message);
}

std::pair<std::string, std::string> WebSocketConnector::popInputQueue()
{
    std::pair<std::string, std::string> result =
    { "", "" };
    inputQueue.pop(result);
    return result;
}

void WebSocketConnector::pushOutputQueue(
        std::pair<std::string, std::string> message)
{
    outputQueue.push(message);
}

std::pair<std::string, std::string> WebSocketConnector::popOutputQueue()
{
    std::pair<std::string, std::string> result =
    { "", "" };
    outputQueue.pop(result);
    return result;
}

