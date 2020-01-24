//
// Created by karin on 14/01/2020.
//
#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <vector>
#include <sstream>
#include <iterator>
#include <mutex>
#include <sys/socket.h>

#include "MyClientHandler.h"
#include "MySearchable.h"
#include "Searcher.h"
#include "State.h"
#include "CacheManager.h"
#include "ObjectAdapter.h"

extern std::mutex mutex_lock;
using namespace std;

void MyClientHandler::handleClient(int serverSocket, int clientSocket) {
    std::cout << "Handling ..." << std::endl;
    //mutex_lock.lock();
    vector<vector<int>> matVector;
    vector<int> lineVector;
    int len, number;
    string line;
    int firstDigit, lastDigit;
    string notDigitOptions = {',', ' '};
    string digitOptions = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    // Reading the data till 'end'
    int lines = 0;
    int cols = 0;
    while (true) {
        char buffer[1024] = {0};
        //mutex_lock.lock();
        int valread = read(clientSocket, buffer, 1024);
        //mutex_lock.unlock();
        std::string a(buffer);
        len = strlen(buffer);
        line = buffer;
        // deleting the \n
        if(line[line.length()-1]=='\n')
            line.resize(line.length() - 1);
        if (a.find("end") != std::string::npos) {
            // Finished the data
            break;
        } else {
            lineVector.clear();//clear data (of last line)
            for (int i = 0; i < len;) {
                firstDigit = line.find_first_not_of(notDigitOptions, i);
                lastDigit = line.find_first_not_of(digitOptions, firstDigit + 1);
                if (firstDigit != -1) {
                    string b = line.substr(firstDigit, (lastDigit - firstDigit));
                    if (b[0] != '\n') {
                        number = std::stoi(line.substr(firstDigit, (lastDigit - firstDigit)));
                        lineVector.push_back(number);
                    }
                } else {
                    break;//no more numbers
                }
                i = lastDigit;
                if (lines == 0)
                    cols++;
            }
            matVector.push_back(lineVector);
        }

        lines++;
        //std::cout << a << '\n';
    }
    // mutex_lock.unlock();
    lines -= 3;
    cols -= 1;
    cout << "lines: "<<lines << ",cols: " << cols << endl;

    /*cout << "------------PRINT MAT---------------" << endl;
    for (int i = 0; i < matVector.size(); i++) {
        for (int j = 0; j < matVector[i].size(); j++) {
            cout << matVector[i][j] << "  ";
        }
        cout << "" << endl;
    }*/

    // flattening the matrix
    vector<int> flatMat;
    vector<int> lineVector1;
    for (int i = 0; i < lines + 1; i++) {
        for (int j = 0; j < cols + 1; j++) {
            flatMat.push_back(matVector[i][j]);
        }
    }
    std::stringstream result;
    std::copy(flatMat.begin(), flatMat.end(), std::ostream_iterator<int>(result, " "));
    string flatMatrix = result.str().c_str();
    // string flatMatrix = "8 2 8 6 8 2 12 2 4 1 9 9 5 12 1 1 1 2 7 3 1 6 9 3 9 7 7 9 5 6 4 5 1 6 -1 1 7 4 12 2 3 2 5 2 1 12 2 4 5 4 3 3 4 12 2 3 9 6 9 1 6 7 7 5 8 7 2 -1 3 2 5 -1 9 2 1 5 8 9 2 1 2 4 7 8 2 9 8 4 2 2 12 8 8 2 3 3 1 5 12 -1 2 7 1 4 -1 -1 -1 2 -1 5 6 8 6 2 4 12 8 9 9 7 1 2 8 8 2 4 2 1 7 6 8 3 -1 8 1 8 6 1 3 3 2 7 3 4 2 9 12 2 7 6 2 12 7 8 1 -1 5 8 8 1 1 5 8 9 9 1 8 5 1 8 4 5 4 5 8 7 6 6 8 2 2 8 8 8 8 9 3 2 3 5 12 -1 9 2 8 3 8 2 12 12 7 1 8 4 2 12 5 4 7 4 4 6 12 9 2 3 5 12 2 2 3 5 12 5 1 7 5 12 6 6 6 5 8 9 4 3 9 2 12 4 9 5 3 12 3 9 3 4 -1 8 5 2 12 5 2 3 7 6 -1 1 12 2 9 9 1 2 2 -1 2 6 12 1 12 12 2 7 5 2 7 7 6 9 2 3 2 4 9 -1 5 7 -1 9 8 6 3 4 12 2 1 2 6 12 2 6 -1 -1 3 9 9 8 3 7 4 3 4 5 -1 9 3 5 12 2 3 -1 12 2 2 2 7 8 -1 12 2 7 4 8 2 8 7 -1 3 -1 2 -1 7 9 6 7 6 1 12 6 2 5 8 1 2 8 3 2 12 7 12 1 2 6 9 7 3 8 6 2 4 7 7 12 8 2 1 6 2 6 4 6 6 7 5 5 8 2 12 2 6 8 12 8 12 9 9 2 2 2 9 6 5 4 2 7 2 9 4 7 4 5 8 2 2 4 3 6 1 4 7 4 9 -1 5 12 3 4 9 7 12 3 5 2 9 7 2 -1 5 12 7 1 6 6 8 2 12 4 -1 4 -1 2 9 6 5 7 2 4 9 12 4 9 2 9 2 6 7 1 12 5 6 6 5 12 4 5 7 6 8 3 9 1 4 8 2 -1 2 -1 7 8 3 6 6 9 4 6 -1 4 -1 1 4 5 9 2 2 1 9 3 7 2 1 12 5 6 -1 9 12 8 9 1 12 7 2 12 9 12 12 1 9 3 7 5 9 3 8 6 6 7 1 1 5 6 2 7 2 3 4 9 9 9 12 2 8 12 2 8 5 -1 2 5 8 7 2 5 1 3 2 4 3 9 5 9 7 7 2 -1 2 8 4 1 5 9 6 2 4 2 9 1 -1 2 4 4 5 12 2 5 2 3 2 2 2 4 5 3 12 9 3 6 2 9 9 1 4 3 2 12 3 1 8 6 7 4 6 7 5 1 8 4 -1 9 7 5 5 3 12 8 3 3 9 5 6 1 12 7 4 9 9 5 9 8 9 9 1 6 9 7 5 3 5 4 6 3 2 1 9 2 1 5 1 3 8 2 1 2 5 2 9 9 3 4 2 2 2 12 7 2 12 3 7 2 8 9 2 1 2 2 2 3 4 12 3 6 6 1 -1 12 7 1 5 2 3 5 8 12 7 3 2 6 8 5 1 12 2 6 6 8 2 7 -1 2 7 9 5 5 7 1 5 4 3 6 4 12 7 8 2 9 8 3 4 3 8 7 6 6 2 7 9 6 6 2 2 6 5 9 2 3 3 3 12 7 12 6 7 2 9 12 1 2 -1 7 2 5 12 2 8 4 7 8 7 7 5 2 5 7 4 2 4 3 12 6 8 5 2 1 4 9 2 1 4 2 2 2 12 4 9 12 9 12 9 12 7 9 2 1 6 5 3 2 6 4 7 9 12 4 4 9 8 1 7 8 2 2 9 3 8 5 3 7 6 7 4 6 2 7 7 8 6 8 9 1 2 9 3 4 9 2 8 12 1 2 5 9 8 7 9 3 3 12 7 9 8 3 2 12 3 6 9 2 1 8 4 8 1 8 6 2 3 9 1 7 3 8 5 8 5 4 4 12 5 2 9 2 1 9 2 6 8 4 4 -1 -1 -1 12 7 7 2 8 4 4 1 9 8 2 9 8 12 5 5 2 8 1 5 9 9 12 6 5 9 8 1 4 4 7 6 12 4 9 1 8 2 1 6 7 2 8 7 6 12 1 2 9 5 12 7 6 4 9 2 2 5 1 9 2 1 6 8 3 2 8 1 2 6 9 8 3 -1 2 5 5 7 12 1 8 4 4 2 12 12 1 1 2 8 4 8 2 6 8 3 8 5 5 3 8 12 8 5 12 1 12 2 5 2 -1 6 9 2 8 1 3 5 6 2 7 9 2 1 6 8 1 2 1 5 2 2 12 2 4 9 2 2 4 7 4 3 6 9 6 5 12 2 3 1 7 2 2 5 6 12 6 6 12 12 2 1 2 2 7 1 1 8 3 5 2 12 1 8 2 6 3 2 9 3 2 4 9 8 5 3 1 3 2 1 1 6 3 -1 2 4 8 7 3 4 7 6 1 9 7 2 12 4 6 5 7 8 2 12 1 2 6 7 8 2 3 12 9 3 6 4 9 2 12 9 8 2 7 6 6 8 3 7 9 3 7 2 2 3 2 4 5 8 7 2 12 12 4 12 2 12 -1 6 -1 2 6 4 4 12 8 3 2 7 3 8 4 7 3 1 5 6 2 2 2 6 2 1 4 3 1 4 2 5 7 1 6 5 12 7 5 -1 3 4 8 2 2 12 9 3 3 8 7 7 8 12 6 12 2 4 12 2 12 7 8 7 1 9 5 12 4 2 2 9 7 1 8 3 8 9 2 2 5 1 7 1 8 2 12 3 12 5 7 9 12 12 12 2 4 4 2 12 2 2 1 6 9 12 7 4 6 12 8 4 8 2 12 3 1 2 8 1 4 7 9 3 7 3 6 6 6 3 9 9 3 9 3 3 7 5 12 2 8 2 2 5 4 9 8 5 3 2 6 4 12 1 9 5 9 2 6 12 3 4 12 -1 12 7 9 2 1 2 2 4 6 12 2 2 2 3 4 1 4 4 2 4 12 6 2 5 6";
    //string flatMatrix = "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1";
    //string flatMatrix = "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1";

    //string flatMatrix = "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1";

    // Creating the problem
    /*lines=36;
    cols=36;*/
    MySearchable<Point> matrixSearchable = MySearchable<Point>(flatMatrix, lines, cols);
    matrixSearchable.setGoal(lines, cols);
    // Checking if there is a solution to the problem in the cache
    CacheManager<string, string> cacheManager = CacheManager<string, string>(5);
    bool solutionInCache = true;
    // Creating a solution

    string solution;
    try {
        // If the solution is in the cache manager
        solution = cacheManager.get(flatMatrix);
    } catch (const char *e) {
        // If the solution is not in the cache manager - we will solve the problem after we get an error
        solutionInCache = false;
        cout << "not in files" << endl;
    }

    // If there isn't a solution, we will solve the problem
    if (!solutionInCache) {
        ObjectAdapter<Point, string> objectAdapter = ObjectAdapter<Point, string>(matrixSearchable);
        Point p = Point(0, 0);
        solution = objectAdapter.solve(p);
        cacheManager.insert(flatMatrix, solution);
    }
    // sending the solution
    cout << "Solution: " << solution << endl;

    char char_array[solution.length() + 1];
    strcpy(char_array, solution.c_str());
    std::vector<char> vec(solution.c_str(), solution.c_str() + (solution.length() + 1));
    char *a = &vec[0];


    char *y = new char[solution.length() + 1]; // or
// char y[100];

    std::strcpy(y, solution.c_str());

    int is_sent = send(clientSocket, a, solution.length() + 1, 0);
    if (is_sent == -1) {
        std::cout << "Error sending message" << std::endl;
    } else {
        //std::cout << "Hello message sent to server" << std::endl;
    }
    //mutex_lock.unlock();
}

ClientHandler *MyClientHandler::duplicate() {
    auto newClient = new MyClientHandler();
    return newClient;
}