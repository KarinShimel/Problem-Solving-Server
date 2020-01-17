//
// Created by noam on 16/01/2020.
//

#ifndef SEARCHALGO_COMP_BFS_H
#define SEARCHALGO_COMP_BFS_H

#include <queue>
#include "ISearcher.h"

template<typename T>
struct node {
    queue<T> queue;
    string color;
    string<T> parent;
};

template<class T>
class BFS {
    ISearcher<T> searchSolution(ISearchable<T> iSearchable) {

    }

};


#endif //SEARCHALGO_COMP_BFS_H
