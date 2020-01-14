//
// Created by karin on 13/01/2020.
//

#ifndef SEARCHALGO_COMP_CLIENTHANDLER_H
#define SEARCHALGO_COMP_CLIENTHANDLER_H
#include <iostream>

class ClientHandler{
public:
    virtual void handleClient(int serverSocket, int clientSocket){
        std::cout << "Client Handler handleClient() Method" << std::endl;
    }
};


#endif //SEARCHALGO_COMP_CLIENTHANDLER_H