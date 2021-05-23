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
///////////////////////////////////////////////////////////////
class Maze
{
    public:
        Maze();
        Maze(int , int );
        void ResetGrid();
        void Visit( int , int);
        void PrintGrid();
        int get_grid_width();
        int get_grid_height();
        int XYToIndex( int , int );
        int IsInBounds( int , int );
        char* grid;
        void dfs_solver();
        void bfs_solver();
        void set_position(int , int , int);
        bool is_goal(int);
        Node& get_start();
        Node& get_end();

    private:
        int grid_width;
        int grid_height;
        Node start;
        Node end;
        
};
////////////////////////////////////////////////////////////////////
class MazeSolution
{
    public:
        MazeSolution();
        MazeSolution(Maze);
        void dfs_solver(Node);
        void bfs_solver(Node);
        bool is_goal(Node);
        std::list<Node> dfs_helper(Node);

    private:
        Maze maze;
};

