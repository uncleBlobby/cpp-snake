#include <vector>
#include <iostream>
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
        NodeBoard(Board board);

        void printNodeBoard() const;
};

Node::Node(){

};

Node::Node(int argx, int argy, Status argStatus){
    x = argx;
    y = argy;
    status = argStatus;
}

NodeBoard::NodeBoard(Board board){
    for (int i = 0; i < board.getWidth(); i++){
        for (int j = 0; j < board.getHeight(); j++){
            Node newNode = Node(i, j, OPEN);
            nodes.push_back(newNode);
        }
    }
}

void NodeBoard::printNodeBoard() const {
    for (int i = 0; i < nodes.size(); i++){
        std::cout << "Node at X: " << nodes[i].x << " Y: " << nodes[i].y;
        
        switch (nodes[i].status){
            case 0:
                std::cout << " Status: OPEN" << std::endl;
                break;
            case 1:
                std::cout << " Status: FOOD" << std::endl;
                break;
            case 2:
                std::cout << " Status: HAZARD" << std::endl;
                break;
            case 3:
                std::cout << " Status: SNAKE" << std::endl;
                break;
        }
    }
}