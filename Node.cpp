#include "Node.h"

Node::Node(int backboneIndex, std::string kmer)
{
    this->backboneIndex = backboneIndex;
    this->kmer = kmer;
}

bool Node::operator==(const Node& n) const
{
    return this->backboneIndex == n.backboneIndex && this->kmer == n.kmer;
}

bool Node::operator<(const Node& n) const
{
    return this->backboneIndex < n.backboneIndex;
}