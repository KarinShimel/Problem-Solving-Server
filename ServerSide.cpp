//
// Created by karin on 14/01/2020.
//

#include "ServerSide.h"
#include "MySerialServer.h"
#include "MyClientHandler.h"
using namespace std;

namespace boot
{
    int Main::main(int argc, char **argv) {
        MySerialServer mySerialServer = MySerialServer();
        Server* server = &mySerialServer;
        MyClientHandler myClientHandler = MyClientHandler();
        ClientHandler * clientHandler = &myClientHandler;
        server->open(stoi((argv)[1]),clientHandler);
        return 0;
    }
}