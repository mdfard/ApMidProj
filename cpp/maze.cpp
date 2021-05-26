#include"maze.h"
#include <cstring>

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
                    std::cout << grid[XYToIndex(x,y)];
                    }
                std::cout << std::endl;
            }
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
    Node* _parent=new Node(0,0);
    start.parent = _parent;
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