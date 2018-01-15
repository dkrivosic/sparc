#include "Edge.h"

Edge::Edge(std::string transition)
{
    this->transition = transition;
    this->weight = 1.0;
}

Edge::Edge(std::string transition, Node* endNode)
{
    this->transition = transition;
    this->weight = 1.0;
    this->endNode = endNode;
}