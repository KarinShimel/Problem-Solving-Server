//
// Created by karin on 17/01/2020.
//

#ifndef SEARCHALGO_COMP_SEARCHER_H
#define SEARCHALGO_COMP_SEARCHER_H

#include <stack>
#include "ISearcher.h"
template <class Problem,class Solution>
class Searcher : public ISearcher<Problem,Solution>{
    Solution search(MySearchable<Problem> searchable);
    int getNumberOfNodesEvaluated();

};

template<class Problem, class Solution>
Solution Searcher<Problem, Solution>::search(MySearchable<Problem> searchable) {
    return nullptr;
}

template<class Problem, class Solution>
int Searcher<Problem, Solution>::getNumberOfNodesEvaluated() {
    return 0;
}




#endif //SEARCHALGO_COMP_SEARCHER_H
