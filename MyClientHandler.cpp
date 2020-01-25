//
// Created by karin on 14/01/2020.
//
#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <iterator>
#include <mutex>
#include <sys/socket.h>

#include "MyClientHandler.h"
#include "MySearchable.h"
#include "CacheManager.h"
#include "ObjectAdapter.h"

extern std::mutex mutex_lock;
using namespace std;

void MyClientHandler::handleClient(int serverSocket, int clientSocket) {
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
        int valread = read(clientSocket, buffer, 1024);
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
    }
    lines -= 3;
    cols -= 1;
    //cout << "lines: "<<lines << ",cols: " << cols << endl;

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
        //solutionInCache = false; Check for solving all the problems
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
    char char_array[solution.length() + 1];
    strcpy(char_array, solution.c_str());
    std::vector<char> vec(solution.c_str(), solution.c_str() + (solution.length() + 1));
    char *a = &vec[0];
    char *y = new char[solution.length() + 1];
    std::strcpy(y, solution.c_str());

    int is_sent = send(clientSocket, a, solution.length() + 1, 0);
    if (is_sent == -1) {
        std::cout << "Error sending message" << std::endl;
    }
}

ClientHandler *MyClientHandler::duplicate() {
    auto newClient = new MyClientHandler();
    return newClient;
}