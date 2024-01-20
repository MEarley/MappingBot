#include <AStarAlgorithm.cpp>

double time_taken(clock_t start, clock_t end);
bool setContains(set<Node*,Compare> nodeSet, Node* target);
bool listContains(list<Node*> l, Node* target);
bool findPath(Node* start, Node* end, vector<vector<Node>> &mat);
void generateMaze(vector<vector<Node>> &mat, set<Node*> &walls);
int aStarAlgorithm();