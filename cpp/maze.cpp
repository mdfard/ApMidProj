#include"maze.h"
#include <cstring>
#include<memory>
#include <unistd.h>
//defines
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

Maze::Maze() : Maze(5 ,5 ,"dfs")
{

}

Maze::Maze(int width , int height , const char* _way)
            : grid_width{width}
            , grid_height{height}
            , way{_way}
    {
        if(width % 2 ==0)
            grid_width++;
        if(height % 2 ==0)
            grid_height++;

        grid = new char[grid_width * grid_height];

        srand( time(0) ); // seed random number generator.
        ResetGrid();
        Visit(1,1);
        
        
        int start = rand()%((grid_width - 3) + 1) + 1;
        int end = rand()%((grid_width - 3) + 1) + 1;
        set_position(start , end , grid_height);

        PrintGrid();
    }

void Maze::ResetGrid()
    {
        // Fills the grid with walls ('#' characters).
        for (int i=0; i<grid_width*grid_height; ++i)
            {
                grid[i] = '#';
            }
    }

int Maze::XYToIndex( int x, int y )
    {
        // Converts the two-dimensional index pair (x,y) into a
        // single-dimensional index. The result is y * ROW_WIDTH + x.
        return y * grid_width + x;
    }

int Maze::IsInBounds( int x, int y )
    {
        // Returns "true" if x and y are both in-bounds.
        if (x < 0 || x >= grid_width) return false;
        if (y < 0 || y >= grid_height) return false;
        return true;
    }

void Maze::PrintGrid()
    {
    // Displays the finished maze to the screen.
        for (int y=0; y<grid_height; ++y)
            {
                for (int x=0; x<grid_width; ++x)
                    {
                    std::cout << grid[XYToIndex(x,y)] << " ";
                    }
                std::cout << std::endl;
            }
        std::cout << "\n\n" << std::endl;
    }

void Maze::Visit( int x, int y )
    {
        // Starting at the given index, recursively visits every direction in a
        // randomized order.
        // Set my current location to be an empty passage.
        grid[ XYToIndex(x,y) ] = ' ';
        // Create an local array containing the 4 directions and shuffle their order.
        int dirs[4];
        dirs[0] = NORTH;
        dirs[1] = EAST;
        dirs[2] = SOUTH;
        dirs[3] = WEST;
        for (int i=0; i<4; ++i)
            {
                int r = rand() & 3;
                int temp = dirs[r];
                dirs[r] = dirs[i];
                dirs[i] = temp;
             }
        // Loop through every direction and attempt to Visit that direction.
        for (int i=0; i<4; ++i)
            {
            // dx,dy are offsets from current location. Set them based
            // on the next direction I wish to try.
            int dx=0, dy=0;
            switch (dirs[i])
                {
                    case NORTH: dy = -1; break;
                    case SOUTH: dy = 1; break;
                    case EAST: dx = 1; break;
                    case WEST: dx = -1; break;
                }
                // Find the (x,y) coordinates of the grid cell 2 spots
                // away in the given direction.
                int x2 = x + (dx<<1);
                int y2 = y + (dy<<1);
                if (IsInBounds(x2,y2))
                    {
                        if (grid[ XYToIndex(x2,y2) ] == '#')
                            {
                                // (x2,y2) has not been visited yet... knock down the
                                // wall between my current position and that position
                                grid[ XYToIndex(x2-dx,y2-dy) ] = ' ';
                                // Recursively Visit (x2,y2)
                                Visit(x2,y2);
                            }
                    }
            }
    }

int Maze::get_grid_width()
    {
        return grid_width;
    }

int Maze::get_grid_height()
    {
        return grid_height;
    }

void Maze::set_position(int xOfStart, int xOfEnd, int grid_height)
{
    start.parent = new Node(0,0);
    start.set_x(xOfStart);
    start.set_y(0);
    end.set_x(xOfEnd);
    end.set_y(grid_height - 1);
    grid[ XYToIndex(xOfStart , 0) ] = ' ';
    grid[ XYToIndex(xOfEnd , grid_height - 1) ] = ' ';
}

Node& Maze::get_start()
{
    return start;
}

Node& Maze::get_end()
{
    return end;
}

const char* Maze::get_way()
{
    return way;
}

/////////////////////////////////////////////////

MazeSolution::MazeSolution()
{

}

MazeSolution::MazeSolution(Maze _maze)
                :maze{_maze}
{
    if (strcmp(_maze.get_way() , "dfs") == 0)
        dfs_solver(maze.get_start());
    else if ((strcmp(_maze.get_way() , "bfs") == 0))
        {
            std::list<Node> start_point;
            start_point.push_back((maze.get_start()));
            bfs_solver(start_point);
        }

    else if((strcmp(_maze.get_way() , "both") == 0)){
        // dfs
        dfs_solver(maze.get_start());
        
        // bfs
        std::list<Node> start_point;
        start_point.push_back((maze.get_start()));
        bfs_solver(start_point);
    }

    else
        std::cout<< "invalid input of way!!!" <<std::endl;
}

bool MazeSolution::dfs_solver(Node current_state)
{
    static size_t flag{0};
    std::list<Node> ways{solve_helper(current_state)};
    static size_t count{0};

    for(auto item : ways){
        if (not flag){
            count++;
            if(is_goal(item)){
                flag = 1;
                std::list<Node> sol;
                findAnswer(item, sol);
                sol.push_back(maze.get_start());
                sol.push_back(maze.get_end());
                
                std::cout << "*** Maze Solved with dfs Algorithm ***" << std::endl;
                std::cout << "we found answer after check " << count << " nodes" << std::endl;
                
                showAnswer(sol, 0); // colortize answer
                return true;
            }
            else
                dfs_solver(item);
        }
    }

    return false;

}

bool MazeSolution::bfs_solver(std::list<Node>& ch)
{
    static int depth{0};
    static size_t count{0};
    std::list<Node> children;
    for(auto item : ch){
        count++;
        if(is_goal(item)){
            std::list<Node> sol;
            findAnswer(item, sol);
            sol.push_back(maze.get_start());
            sol.push_back(maze.get_end());
            std::cout << "*** Maze Solved with bfs Algorithm ***" << std::endl;
            std::cout << "we found answer after check " << count << " nodes" << std::endl;
            showAnswer(sol, 1); // colorize answer
            return true;
        }
        visited.push_back(item);
    }
    for(auto& item1 : ch){
        std::list<Node> temp = solve_helper(item1);
        for(auto& item2: temp){
            item2.parent = &item1;
            children.push_back(item2);
        }
    }
    depth++;
    if (depth > 2000){
        std::cout << "We can't find answer until depth:2000 !!!" << std::endl;
        return false;
    }
    bfs_solver(children);
    return false;
}


std::list<Node> MazeSolution::solve_helper(Node& current_state)
{
    std::list<Node> ways;
    int x{current_state.get_x()};
    int y{current_state.get_y()};
    
    int dirs[4];
    dirs[0] = NORTH;
    dirs[1] = EAST;
    dirs[2] = SOUTH;
    dirs[3] = WEST;

    for (int i=0; i<4; ++i)
        {
        int dx=0, dy=0;
        switch (dirs[i])
            {
                case NORTH: dy = -1; break;
                case SOUTH: dy = 1; break;
                case EAST: dx = 1; break;
                case WEST: dx = -1; break;
            }
            int x2{x + dx};
            int y2{y + dy};
            if (maze.IsInBounds(x2,y2))
                {
                    if (maze.grid[ maze.XYToIndex(x2,y2) ] == ' ')
                        {      
                            Node* child = new Node(x2,y2);
                            if (!(isEqualToParent(*child, current_state))){
                                if (!checkInVisited(*child)){
                                    child->parent = &current_state;
                                    ways.push_back(*child);
                                }
                            }
                        }
                }
            }
    return ways;
}

bool MazeSolution::checkInVisited(Node& node){
    for (auto item:visited){
        if (node.get_x() == item.get_x() && node.get_y() == item.get_y())
            return true;
    }
    return false;
}

void MazeSolution::showAnswer(std::list<Node>& sol, size_t algo = 0){
    for (int y=0; y<maze.get_grid_height(); ++y){
        for (int x=0; x<maze.get_grid_width(); ++x){
            int flag{0};
            for (auto item: sol){
                if (item.get_x() == x && item.get_y() == y){
                    if (algo){
                        std::cout <<  "\u001b[43m" << maze.grid[maze.XYToIndex(x,y)] << " " << "\u001b[40m";
                    }
                    else{
                        std::cout <<  "\u001b[45m" << maze.grid[maze.XYToIndex(x,y)] << " " << "\u001b[40m";
                    }
                    flag = 1;
                    break;
                }
            }
            if (!flag)
                std::cout << maze.grid[maze.XYToIndex(x,y)] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n\n" << std::endl;
}


void MazeSolution::findAnswer(Node& node, std::list<Node>& sol){
    if (!(node.get_x() == maze.get_start().get_x() && node.get_y() == maze.get_start().get_y())){
        sol.push_back(node);
        findAnswer(*node.parent, sol);
    }
}


bool MazeSolution::isEqualToParent(Node& node, Node& current)
{

    if (node.get_x() == current.parent->get_x() && node.get_y() == current.parent->get_y())
    {
        return true;
    }
    return false;
}

bool MazeSolution::is_goal(Node current)
{
    if(current.get_x() == maze.get_end().get_x() && current.get_y() == maze.get_end().get_y() - 1  )
        return true;
    return false;
}


///////////////////////////////

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
