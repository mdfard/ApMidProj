#include "mazesolution.h"

MazeSolution::MazeSolution()
{

}

MazeSolution::MazeSolution(Maze _maze)
                :maze{_maze}
{
    dfs_solver(maze.get_start());
    if (strcmp(_maze.get_way() , "dfs") == 0)
        dfs_solver(maze.get_start());
    else if ((strcmp(_maze.get_way() , "bfs") == 0))
        bfs_solver(maze.get_start());
    else
        std::cout<< "invalid input of way!!!" <<std::endl;
}

bool MazeSolution::dfs_solver(Node current_state)
{
    static size_t flag{0};
    std::list<Node> ways{dfs_helper(current_state)};

    for(auto item : ways){
        if (not flag){
            if(is_goal(item)){
                std::cout << "congratulations!!!" << std::endl;
                flag = 1;
                std::list<Node> sol;
                findAnswer(item, sol);
                sol.push_back(maze.get_start());
                sol.push_back(maze.get_end());
                
                showAnswer(sol); // colortize answer
                return true;
            }
            else
                dfs_solver(item);
        }
    }
    return false;

}


std::list<Node> MazeSolution::dfs_helper(Node& current_state)
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
                            Node* child =new Node(x2,y2);
                            child->parent = &current_state;
                            if (!(isEqualToParent(*child, current_state))){
                                ways.push_back(*child);
                            }
                            else{
                                
                            }
                        }
                }
            }
    return ways;
}


void MazeSolution::showAnswer(std::list<Node>& sol){
    for (int y=0; y<maze.get_grid_height(); ++y){
        for (int x=0; x<maze.get_grid_width(); ++x){
            int flag{0};
            for (auto item: sol){
                if (item.get_x() == x && item.get_y() == y){
                    std::cout <<  "\u001b[43m" << maze.grid[maze.XYToIndex(x,y)] << " " << "\u001b[40m";
                    flag = 1;
                    break;
                }
            }
            if (!flag)
                std::cout << maze.grid[maze.XYToIndex(x,y)] << " ";
        }
        std::cout << std::endl;
    }
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

void MazeSolution::bfs_solver(Node current_state)
{
    
}

bool MazeSolution::is_goal(Node current)
{
    if(current.get_x() == maze.get_end().get_x() && current.get_y() == maze.get_end().get_y() - 1  )
        return true;
    return false;
}