#ifndef MAZESOLUTION
#define MAZESOLUTION
#include <list>
#include <iostream>
#include "node.h"
#include "maze.h"

class MazeSolution
{
    public:
        MazeSolution();
        MazeSolution(Maze);
        bool dfs_solver(Node);
        bool bfs_solver(std::list<Node>&);
        void findAnswer(Node&, std::list<Node>&);
        void showAnswer(std::list<Node>&, size_t);
        bool is_goal(Node);
        bool isEqualToParent(Node&, Node&);
        std::list<Node> solve_helper(Node&);
        bool checkInVisited(Node& node);
        
    private:
        Maze maze;
        std::list<Node> visited;
};

#endif