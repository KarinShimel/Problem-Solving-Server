//
// Created by karin on 16/01/2020.
//

#ifndef SEARCHALGO_COMP_OBJECTADAPTER_H

#define SEARCHALGO_COMP_OBJECTADAPTER_H
#include "Solver.h"
#include "ISearchable.h"

template <class Problem,class Solution>
class ObjectAdapter : public Solver<Problem,Solution>{
    MySearchable<Problem> searchable;
    ObjectAdapter(MySearchable<Problem> searchable1){
        this->searchable = searchable1;
    }
    Solution solve(Problem){
        // searcher.search(searchable)
    }
};


#endif //SEARCHALGO_COMP_OBJECTADAPTER_H
