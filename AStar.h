//
// Created by karin on 21/01/2020.
//

#ifndef PART2_ASTAR_H
#define PART2_ASTAR_H


#include "Searcher.h"
#include "algorithm"

using namespace std;

template<class Problem, class Solution>
class AStar : public Searcher<Problem, Solution> {
public:
    struct stateStar {
        State<Point> state;
        int h;
        int f;
        stateStar *cameFrom;
    };
    State<Problem> goalState;
    int nodesEvaluated = 0;

    virtual int getNumberOfNodesEvaluated() {
        return this->nodesEvaluated;
    }

    string getPath(stateStar goal, MySearchable<Problem> searchable) {
        // Getting the path from the goal to the start
        stack<string> pathQ;
        int steps=0;
        while (!((goal.state) == searchable.getInitial())) {
            stateStar *from = goal.cameFrom;
            string a = searchable.findDirection((goal.state), from->state);
            pathQ.push(a);
            goal = *from;
        }
        string path;
        while (!pathQ.empty()) {
            steps++;
            path += pathQ.top();
            path += ", ";
            pathQ.pop();
        }
        path.resize(path.size() - 2);
        return path;
    }

    int getHeuVal(State<Problem> n) {
        // Getting the h value
        Point goalPoint = goalState.getState();
        Point currPoint = n.getState();
        return (abs(currPoint.getI() - goalPoint.getI()) + abs(currPoint.getJ() - goalPoint.getJ()));
    }

    bool doesExistsInList(stateStar v, list<stateStar> list, int *f) {
        // Checking if the state is in the list given, and checking the f value
        for (stateStar stateStar : list) {
            if (stateStar.state == v.state) {
                *f = stateStar.f;
                return true;
            }
        }
        return false;
    }

    Solution search(MySearchable<Problem> searchable) {
        // Setting the data we need later on
        goalState = searchable.getGoalState();
        Solution s;
        list<stateStar> closedList;
        auto cmp = [](stateStar left, stateStar right) {
            return ((left.f > right.f) && (left.state.cost > right.state.cost));
        };
        priority_queue<stateStar, vector<stateStar>, decltype(cmp)> openList(cmp);
        State<Point> n = (State<Point>) (searchable.getInitial());
        stateStar first;
        first.state = (State<Point>) (searchable.getInitial());
        first.cameFrom = NULL;
        first.f = (int) (n.getCost() + getHeuVal(n));
        first.h = getHeuVal(n);
        openList.push(first);

        while (!openList.empty()) {
            // for each point in the open list
            stateStar temp = openList.top();
            stateStar *node = new stateStar();
            node->state = temp.state;
            node->cameFrom = temp.cameFrom;
            node->f = temp.f;
            node->h = temp.h;
            nodesEvaluated++;

            openList.pop();
            list<State<Point>> neighbors = searchable.getAllPossibleStates(node->state);
            list<stateStar> starNeighbors;

            while (!neighbors.empty()) {
                // Changing the neighbors to the structs we created
                State<Point> curr = neighbors.front();
                stateStar *neighbor = new stateStar();
                neighbor->state = curr;
                neighbor->cameFrom = node;
                neighbor->f = (int) (curr.getCost() + getHeuVal(curr));
                neighbor->h = getHeuVal(curr);
                // pushing the neighbor to the new struct list
                starNeighbors.push_back(*neighbor);
                // popping from the neighbors list
                neighbors.pop_front();
            }
            // for each neighbor
            for (stateStar starNeighbor: starNeighbors) {
                if (starNeighbor.state == goalState) {
                    // We reached the goal!!
                    return getPath((stateStar) starNeighbor, searchable);
                }

                list<stateStar> temp;
                bool xInOpenList = false;
                int t;
                while (!openList.empty()) {
                    // Checking if x is in the open list
                    if (starNeighbor.state == openList.top().state) {
                        xInOpenList = true;
                        t = openList.top().f;
                    }
                    // popping all the open list
                    temp.push_back(openList.top());
                    openList.pop();
                }
                while (!temp.empty()) {
                    // Putting them back into the open list
                    openList.push(temp.front());
                    temp.pop_front();
                }
                if (xInOpenList) {
                    if (t <= starNeighbor.f)
                        continue;
                }
                if (doesExistsInList(starNeighbor, closedList, &t) && t <= starNeighbor.f)
                    continue;
                else
                    openList.push(starNeighbor);
            }
            closedList.push_back(*node);
        }
        return "no path found";
    }
};

#endif //PART2_ASTAR_H
