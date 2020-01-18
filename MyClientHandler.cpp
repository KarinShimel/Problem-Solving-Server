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


#include "MyClientHandler.h"
#include "MySearchable.h"
#include "State.h"
#include "CacheManager.h"
#include "ObjectAdapter.h"

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
    int lines = 0;
    int cols = 0;
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
                lastDigit = line.find_first_not_of(digitOptions, firstDigit + 1);
                if (firstDigit != -1) {
                    number = stoi(line.substr(firstDigit, (lastDigit - firstDigit)));
                    lineVector.push_back(number);
                } else {
                    break;//there are no more numbers
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
    lines -= 3;
    cols -= 1;
    cout << lines << "," << cols << endl;
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
    // Creating the problem
    MySearchable<Point> matrixSearchable = MySearchable<Point>(flatMatrix, lines, cols);
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
        ObjectAdapter<Point,string> objectAdapter = ObjectAdapter<Point,string>(matrixSearchable);
        Point p = Point(0,0);
        solution = objectAdapter.solve(p);
    }
    // sending the solution
    cout << "Solution: " << solution << endl;


}