//
// Created by karin on 13/01/2020.
//

#ifndef SEARCHALGO_COMP_SERVERSIDE_H
#define SEARCHALGO_COMP_SERVERSIDE_H

#include "ClientHandler.h"


namespace server_side {
    class Server {

    public:
        void virtual open(int port, ClientHandler * clientHandler) {
            std::cout << "Server Open Method" << std::endl;
        };

        void virtual stop() {
            std::cout << "Server Stop Method" << std::endl;
        };

        virtual ~Server() {}
    };
}

using namespace server_side;

namespace boot {
    class Main {
    public:
        int main(int argc, char *argv[]);
    };
}
#endif //SEARCHALGO_COMP_SERVERSIDE_H
