#include "mazeSolution.h"
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3



Node& Maze::get_start()
{
    return start;
}

Node& Maze::get_end()
{
    return end;
}


Node::Node()
{

}

Node::Node(int _x, int _y)
        :x{_x}
        ,y{_y}
{

}

void Node::set_x(int length)
{
    x = length;
}

void Node::set_y(int width)
{
    y = width;
}

int Node::get_x()
{
    return x;
}

int Node::get_y()
{
    return y;
}
