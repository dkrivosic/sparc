#pragma once
#include <string>

class Node
{
    public:
        int backboneIndex;
        std::string kmer;
        Node(int, std::string);
        bool operator==(const Node&) const;
        bool operator<(const Node&) const;
};