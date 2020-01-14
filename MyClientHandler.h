//
// Created by karin on 14/01/2020.
//

#ifndef SEARCHALGO_COMP_MYCLIENTHANDLER_H
#define SEARCHALGO_COMP_MYCLIENTHANDLER_H

#include "ClientHandler.h"

class MyClientHandler : public ClientHandler{
    void handleClient(int serverSocket, int clientSocket) override ;
};


#endif //SEARCHALGO_COMP_MYCLIENTHANDLER_H
