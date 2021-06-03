#ifndef NODE
#define NODE



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