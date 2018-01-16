#pragma once
#include <string>

class Node
{
    public:
        int backboneIndex;
        std::string kmer;
        std::string insertString;
        Node(int, std::string);
        Node(int, std::string, std::string);
        bool operator==(const Node&) const;
        bool operator!=(const Node&) const;
        bool operator<(const Node&) const;
};