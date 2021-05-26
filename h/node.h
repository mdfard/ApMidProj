#ifndef NODE
#define NODE


#include "mazesolution.h"
#include "maze.h"

class MazeSolution;
class Maze;

class Node
{
    public:
        Node();
        Node(int , int);
        Node* parent;
        std::list<Node*> child;
        void set_x(int);
        void set_y(int);
        int get_x();
        int get_y();
    private:
        int x; //position of node
        int y; //position of node
};

#endif