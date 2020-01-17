//
// Created by noam on 16/01/2020.
//

#ifndef SEARCHALGO_COMP_ISEARCHER_H
#define SEARCHALGO_COMP_ISEARCHER_H

#include "State.h"
#include "ISearchable.h"
#include <list>

template<class T>
class ISearcher {
private:
    list <T> list;
public:
    //add new element
    void addToList(ISearchable<T> element) {
        this->list.push_back(element);
    }

    //delete last element
    void popFromList() {
        this->list.pop();
    }

    virtual ISearcher<T> searchSolution(ISearchable<T> iSearchable) = 0;

    virtual ~ISearcher() {}
};


#endif //SEARCHALGO_COMP_ISEARCHER_H
