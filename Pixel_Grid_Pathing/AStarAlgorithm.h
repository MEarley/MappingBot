#ifndef AStarAlgorithm
#define AStarAlgorithm

#include <set>
#include <vector>
#include <list>
#include <math.h>

extern int SCALE;
const int SCREENWIDTH = 800;
const int SCREENHEIGHT = 450;
extern int xOFFSET; //SCREENWIDTH / 2;
extern int yOFFSET; //SCREENHEIGHT / 2;
const Color START_COLOR = BLUE;
const Color END_COLOR = ORANGE;
const Color WALL_COLOR = GRAY;
const Color PATH_COLOR = GREEN;
const Color BACKGROUND_COLOR = RAYWHITE;
const Color TEXT_COLOR = Fade(BLACK, 0.75);

enum nodeTypes{WALL, PATH, VOID};

class NodeType{
    public:
    Color color = BACKGROUND_COLOR;
    nodeTypes name = VOID;

    NodeType(){}

    NodeType(Color color_, nodeTypes name_){
        color = color_;
        name = name_;
    }

    std::string to_string(){
        switch(name){
            case VOID :
                return "Void";
            case PATH :
                return "Path";
            case WALL :
                return "Wall";
        }
        return "Error: Undefinable type";
    }
};

class Node{
    int x = 9999;
    int y = 9999;
    public:
    Node* parent = NULL;
    NodeType nType;
    int initial = 9999;  // Distance from Node to start
    int heuristic  = 9999;  // Distance from Node to end
    int cost = 9999;  // initial + heuristic

    Node(){
        x = 0 + xOFFSET;
        y = 0 + yOFFSET;
        nType = NodeType();
    }

    Node(int x_, int y_){
        x = x_ + xOFFSET;
        y = y_ + yOFFSET;
        nType = NodeType();
    }

    Node(Color color_,nodeTypes name_){
        nType.color = color_;
        nType.name = name_;
    }

    Node(int x_, int y_, Color color_,nodeTypes name_){
        x = x_ + xOFFSET;
        y = y_ + yOFFSET;
        nType.color = color_;
        nType.name = name_;
    }

    std::string to_string(){
        return nType.to_string();
    }

    int get_distance(Node goal){
        int distance = (int)ceil(sqrt(pow(goal.get_x() - x,2) + pow(goal.get_y() - y,2)) * 10);
        return distance;
    }

    int set_heuristic(Node end){
        heuristic = get_distance(end);
        update_cost();
        return heuristic ;
    }

    int set_initial(Node start){
        initial = get_distance(start);
        update_cost();
        return initial;
    }

    void set_initial(int distance){
        initial = distance;
        update_cost();
        return;
    }

    void update_cost(){
        cost = heuristic + initial;
    }

    int get_x(){
        return x;
    }
    int get_y(){
        return y;
    }

    int get_x_scaled(){
        return (x * SCALE);
    }
    int get_y_scaled(){
        return (y * SCALE);
    }
    void set_x(int x_){
        x = x_;
    }
    void set_y(int y_){
        y = y_;
    }
};

class Compare {
    public:
    bool operator()(Node* const& a, Node* const& b){
        return a->cost > b->cost;
    }
};

double time_taken(clock_t start, clock_t end);
bool setContains(std::set<Node*,Compare> nodeSet, Node* target);
bool listContains(std::list<Node*> l, Node* target);
bool findPath(Node* start, Node* end, std::vector<std::vector<Node>> &mat);
void generateMaze(std::vector<std::vector<Node>> &mat, std::set<Node*> &walls);
int aStarAlgorithm(std::vector<std::vector<Node>> &matrix, Node* start, Node* end);

#endif