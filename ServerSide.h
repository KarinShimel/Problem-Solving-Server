//
// Created by karin on 13/01/2020.
//

#ifndef SEARCHALGO_COMP_SERVERSIDE_H
#define SEARCHALGO_COMP_SERVERSIDE_H

#include "ClientHandler.h"

namespace server_side{
    class Server {

    public:
        void virtual open (int port,ClientHandler clientHandler);
        void virtual stop();
        virtual ~Server() {}
    };


}
#endif //SEARCHALGO_COMP_SERVERSIDE_H
