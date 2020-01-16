//
// Created by karin on 16/01/2020.
//

#ifndef SEARCHALGO_COMP_CACHEMANAGER_H
#define SEARCHALGO_COMP_CACHEMANAGER_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <functional>
#include <map>
#include <fstream>
#include <stack>

using namespace std;

template<class T>
class CacheManager {
private:
    unsigned int cacheSize;
    unordered_map<string, pair<T, list<string>::iterator>> cacheMap;
    list<string> data;
public:
    CacheManager(int num) {
        this->cacheSize = num;
    }

    void insert(string, T);

    T get(string key);

    void foreach(function<void(T &)> function);

    void use(typename unordered_map<string, pair<T, list<string>::iterator>>::iterator &iterator) {
        data.erase(iterator->second.second);
        data.push_front(iterator->first);
        iterator->second.second = data.begin();
    }
};

template<class T>
void CacheManager<T>::insert(string key, T obj) {
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
    ofstream myFile;
    string file = T::class_name + key;
    myFile.open(file, ios::binary | ios::out);
    myFile.write((char *) &obj, sizeof(T));
    myFile.close();
}

template<class T>
void CacheManager<T>::foreach(function<void(T &)> function) {
    for (string key: data) {
        function(cacheMap[key].first);
    }
}

template<class T>
T CacheManager<T>::get(string key) {
    auto item = cacheMap.find(key);
    if (item == cacheMap.end()) {
        // check if in data
        ifstream in_file;
        string file_name = T::class_name + key;
        in_file.open(file_name, ios::binary | ios::in);
        if (!in_file) {
            // if not in data
            throw "an error";
        }
        // getting the object from the file
        T object;
        in_file.read((char *) &object, sizeof(T));
        this->insert(key, object);
        in_file.close();
        return object;
    }
    // informing the algorithm we used the object
    use(item);
    return item->second.first;
}
#endif //SEARCHALGO_COMP_CACHEMANAGER_H
