#include "Node.h"

Node::Node(int backboneIndex, std::string kmer)
{
    this->backboneIndex = backboneIndex;
    this->kmer = kmer;
    this->insertString = "";
}

Node::Node(int backboneIndex, std::string kmer, std::string insertString)
{
    this->backboneIndex = backboneIndex;
    this->kmer = kmer;
    this->insertString = insertString;
}

bool Node::operator==(const Node& n) const
{
    return this->backboneIndex == n.backboneIndex && this->kmer == n.kmer && this->insertString == n.insertString;
}

bool Node::operator!=(const Node& n) const
{
    return !(*this == n);
}

bool Node::operator<(const Node& n) const
{
    if (this->backboneIndex == n.backboneIndex)
    {
        return this->insertString < n.insertString;
    }
    
    return this->backboneIndex < n.backboneIndex;
}