
#include"node.h"

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
