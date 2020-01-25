//
// Created by karin on 16/01/2020.
//

#ifndef SEARCHALGO_COMP_OBJECTADAPTER_H

#define SEARCHALGO_COMP_OBJECTADAPTER_H

#include "Solver.h"
#include "ISearchable.h"
#include "Searcher.h"
#include "BestFirstSearch.h"
#include "BreadthFirstSearch.h"
#include "DepthFirstSearch.h"
#include "AStar.h"

template<class Problem, class Solution>
class ObjectAdapter : public Solver<Problem, Solution> {

public:
    MySearchable<Problem> searchable;

    Solution solve(Problem) {
        DepthFirstSearch<Problem, Solution> bfs = DepthFirstSearch<Problem, Solution>();
        Solution s = bfs.search(this->searchable);
        //cout << s << endl;
        return s;
    }

    ObjectAdapter(MySearchable<Problem> searchable1) {
        this->searchable = searchable1;
    }
};


#endif //SEARCHALGO_COMP_OBJECTADAPTER_H
