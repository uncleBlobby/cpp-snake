#include <vector>
#include <iostream>
#include <map>
#include <tuple>
#include "Game.h"

enum Status { OPEN = 0, FOOD, HAZARD, SNAKE };

class Node {
    public:
        unsigned int x;
        unsigned int y;
        Status status;

        Node();
        Node(int argx, int argy, Status argStatus);
};

class NodeBoard {
    public:
        std::vector<Node> nodes;
        
        

        // initialize empty nodeboard with all nodes set to open.
        NodeBoard();

        void printNodeBoard() const;
};

Node::Node(){

};

Node::Node(int argx, int argy, Status argStatus){
    x = argx;
    y = argy;
    status = argStatus;
}
