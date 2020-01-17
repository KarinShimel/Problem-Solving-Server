//
// Created by karin on 17/01/2020.
//

#ifndef SEARCHALGO_COMP_SEARCHER_H
#define SEARCHALGO_COMP_SEARCHER_H

#include "ISearcher.h"
template <class Problem,class Solution>
class Searcher : public ISearcher<Problem,Solution>{
    Solution search(ISearchable<Problem> searchable);
    int getNumberOfNodesEvaluated();
};


#endif //SEARCHALGO_COMP_SEARCHER_H
