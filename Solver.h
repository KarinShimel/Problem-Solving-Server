//
// Created by karin on 16/01/2020.
//

#ifndef SEARCHALGO_COMP_SOLVER_H
#define SEARCHALGO_COMP_SOLVER_H
template <class Problem,class Solution>
class Solver{
    virtual Solution solve(Problem)=0;
};

#endif //SEARCHALGO_COMP_SOLVER_H
