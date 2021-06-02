#ifndef MAZE
#define MAZE
#include <iostream>
#include <list>



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