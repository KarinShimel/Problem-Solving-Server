//
// Created by karin on 14/01/2020.
//
#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>

#include "MyClientHandler.h"
#include "CacheManager.h"

using namespace std;

void MyClientHandler::handleClient(int serverSocket, int clientSocket) {
    //std::cout << "Handling ..." << std::endl;
    vector<vector<int>> matVector;
    vector<int> lineVector;
    int len, number;
    string line;
    int firstDigit, lastDigit;
    string notDigitOptions = {',', ' '};
    string digitOptions = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    // Reading the data till 'end'
    while (true) {
        char buffer[1024] = {0};
        int valread = read(clientSocket, buffer, 1024);
        std::string a(buffer);
        len = strlen(buffer);
        line = buffer;
        if (a.find("end") != std::string::npos) {
            // Finished the data
            break;
        } else {
            lineVector.clear();//clear data (of last line)
            for (int i = 0; i < len;) {
                firstDigit = line.find_first_not_of(notDigitOptions, i);
                lastDigit = line.find_first_not_of(digitOptions, firstDigit+1);
                if (firstDigit != -1) {
                    number = stoi(line.substr(firstDigit, (lastDigit - firstDigit)));
                    lineVector.push_back(number);
                } else {
                    break;//there are no more numbers
                }
                i = lastDigit;
            }
            matVector.push_back(lineVector);
        }


       // std::cout << a << '\n';
    }
    cout << "------------PRINT MAT---------------" << endl;
    for (int i = 0; i < matVector.size(); i++) {
        for (int j = 0; j < matVector[i].size(); j++) {
            cout << matVector[i][j] << "  ";
        }
        cout << "" << endl;
    }


// Creating the problem
//Solver<string,string> solver = Solver<string,string>();
// Creating a solution
// If the solution is in the cache manager
// If the solution is not in the cache manager - we will solve the problem
// Updating the solution in the cache manager
}