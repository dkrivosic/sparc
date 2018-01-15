#pragma once
#include "Node.h"
#include <string>


class Edge
{
    public:
        std::string transition;
        float weight;
        Node *endNode;
        Edge(std::string);
        Edge(std::string, Node*);
        bool operator==(const Edge&) const;
        bool operator<(const Edge&) const;
};