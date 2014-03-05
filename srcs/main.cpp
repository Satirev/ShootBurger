#include <iostream>
#include <string>
#include "Json/JsonSerializer.h"
#include "Json/HelloRequest.h"
#include "WebSocket/Server.h"
#include "Common/Dispatcher.h"
#include "Lobby.h"

int main()
{
    Lobby lobby;
    lobby.open();
    int stop;
    Server server(boost::asio::ip::address::from_string("10.0.2.15"), 9002);
    Dispatcher dispatcher(3, &lobby);
    server.Run();
    dispatcher.RunWorkers();

    std::cin >> stop;
    lobby.close();
    server.Stop();
    server.Wait();

    return 0;
}
