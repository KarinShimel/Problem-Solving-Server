//
// Created by karin on 01/12/2019.
//

#ifndef E2_EX2_H
#define E2_EX2_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <functional>
#include <map>
#include <fstream>
#include <stack>

using namespace std;

#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>


using namespace std;

template<class Problem, class Solution>
class CacheManager {
private:
    unsigned int cacheSize;
    unordered_map<Problem, pair<Solution, typename list<Problem>::iterator>> cacheMap;
    list<Problem> data;
public:
    CacheManager(int num) {
        this->cacheSize = num;
    }


    void insert(Problem, Solution);

    Solution get(Problem key);

    void foreach(function<void(Solution &)> function);

    void use(typename unordered_map<Problem, pair<Solution, typename list<Problem>::iterator>>::iterator &iterator) {
        data.erase(iterator->second.second);
        data.push_front(iterator->first);
        iterator->second.second = data.begin();
    }
};

template<class Problem, class Solution>
void CacheManager<Problem, Solution>::insert(Problem key, Solution obj) {
    auto item = cacheMap.find(key);
    // if the key exists - setting the value
    if (item != cacheMap.end()) {
        use(item);
        cacheMap[key] = {obj, data.begin()};
        return;
    } else {
        // key doesnt exist - checking the map size
        if (cacheMap.size() == cacheSize) {
            // kicking out the last recent
            cacheMap.erase(data.back());
            data.pop_back();
        }
        // inserting new pair
        data.push_front(key);
        cacheMap.insert({key, {obj, data.begin()}});
    }
    // writing to the files
    string filename = key;
    for (int i = filename.length() - 1; i >= 0; --i) {
        if (filename[i] == ' ')
            filename.erase(i, 1);
    }
    filename.resize (255);
    ofstream myFile;
    myFile.open(filename, ios::app);
    if (myFile.is_open()) {
        myFile << obj << endl;
    }
    myFile.close();
}

template<class Problem, class Solution>
void CacheManager<Problem, Solution>::foreach(function<void(Solution &)> function) {
    for (Problem key: data) {
        function(cacheMap[key].first);
    }
}

template<class Problem, class Solution>
Solution CacheManager<Problem, Solution>::get(Problem key) {
    auto item = cacheMap.find(key);
    if (item == cacheMap.end()) {
        // check if in data
        ifstream in_file;
        string filename = key;
        for (int i = filename.length() - 1; i >= 0; --i) {
            if (filename[i] == ' ')
                filename.erase(i, 1);
        }
        filename.resize (255);
        in_file.open(filename,ios::in);
        if (!in_file) {
            // if not in data
            throw "an error";
        }
        // getting the object from the file
        Solution s;
        getline(in_file,s);
        //in_file.read(object);
        this->insert(key, s);
        in_file.close();
        return s;
    }
    // informing the algorithm we used the object
    use(item);
    return item->second.first;
}


#endif //E2_EX2_H
