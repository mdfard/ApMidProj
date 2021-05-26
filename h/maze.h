#ifndef MAZE
#define MAZE
#include <iostream>
#include <list>
#include "node.h"
#include "mazesolution.h"

class MazeSolution;
class Node;

class Maze
{
    public:
        Maze();
        Maze(int , int , const char*);
        void ResetGrid();
        void Visit( int , int);
        void PrintGrid();
        void set_position(int , int , int);
        int get_grid_width();
        int get_grid_height();
        int XYToIndex( int , int );
        int IsInBounds( int , int );
        char* grid;
        Node& get_start();
        Node& get_end();
        const char* get_way();
        
    private:
        int grid_width;
        int grid_height;
        const char* way;
        Node start;
        Node end;
        
};

#endif