//
// Created by karin on 14/01/2020.
//
#include <iostream>
#include <unistd.h>

#include "MyClientHandler.h"
#include "CacheManager.h"
using namespace std;

void MyClientHandler::handleClient(int serverSocket, int clientSocket) {
    //std::cout << "Handling ..." << std::endl;
    // Reading the data till 'end'
    while (true) {
        char buffer[1024] = {0};
        int valread = read(clientSocket, buffer, 1024);
        std::string a(buffer);
        if (a.find("end") != std::string::npos) {
            // Finished the data
            break;
        }
        std::cout << a << '\n';
    }

    // Creating the problem
    //Solver<string,string> solver = Solver<string,string>();
    // Creating a solution
    // If the solution is in the cache manager
    // If the solution is not in the cache manager - we will solve the problem
    // Updating the solution in the cache manager
}