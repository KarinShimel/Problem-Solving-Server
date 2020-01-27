//
// Created by karin on 14/01/2020.
//

#include "ServerSide.h"
#include "MyClientHandler.h"
#include "MyParallelServer.h"
using namespace std;

namespace boot
{
    int Main::main(int argc, char **argv) {
        // Creating the specific server data - a parallel server
        MyParallelServer mySerialServer = MyParallelServer();
        Server* server = &mySerialServer;
        // a specific client handler to handle a matrix
        MyClientHandler myClientHandler = MyClientHandler();
        ClientHandler * clientHandler = &myClientHandler;
        // Running the server and handler
       if(argc<2)
           server->open(5600,clientHandler);
       else
           server->open(stoi((argv)[1]),clientHandler);
        return 0;
    }
}