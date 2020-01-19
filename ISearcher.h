//
// Created by karin on 17/01/2020.
//

#ifndef SEARCHALGO_COMP_ISEARCHER_H
#define SEARCHALGO_COMP_ISEARCHER_H

#include "ISearchable.h"


template <class Problem,class Solution>
class ISearcher{
    virtual Solution search(MySearchable<Problem> searchable)=0;
    virtual int getNumberOfNodesEvaluated()=0;
};





#endif //SEARCHALGO_COMP_ISEARCHER_H
