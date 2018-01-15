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

bool Edge::operator==(const Edge& e) const
{
    return this->transition == e.transition && this->endNode == e.endNode;
}

bool Edge::operator<(const Edge& e) const
{
    if (this->transition == e.transition)
    {
        return this->endNode < e.endNode;
    }
    return this->transition < e.transition;
}