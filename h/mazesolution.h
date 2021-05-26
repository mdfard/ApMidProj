#ifndef MAZESOLUTION
#define MAZESOLUTION

#include "node.h"
#include "maze.h"

class Node;
class Maze;

class MazeSolution
{
    public:
        MazeSolution();
        MazeSolution(Maze);
        bool dfs_solver(Node);
        void bfs_solver(Node);
        void findAnswer(Node&, std::list<Node>&);
        void showAnswer(std::list<Node>&);
        bool is_goal(Node);
        bool isEqualToParent(Node&, Node&);
        std::list<Node> dfs_helper(Node&);
        
    private:
        Maze maze;
};

#endif
