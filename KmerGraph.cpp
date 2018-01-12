#include "KmerGraph.h"
#include "Node.h"
#include "Edge.h"
#include "backbone.h"
#include <string>
#include <map>
#include <vector>

#include <iostream>

KmerGraph::KmerGraph(Backbone *backbone, int k, int g)
{
    this->k = k;
    this->g = g;
    this->initialNode = nullptr;
    initializeGraph(backbone->value);
}

KmerGraph::~KmerGraph()
{

}

void KmerGraph::initializeGraph(std::string backbone)
{
    int len = backbone.length();
    int i = 0;
    Edge *e = nullptr;

    while (i <= len - 1)
    {
        std::string kmer = backbone.substr(i, k);
        
        Node *n = new Node(i, kmer);

        if (e != nullptr)
        {
            e->endNode = n;
        }
        else
        {
            initialNode = n;
        }

        i += k;
        if (i >= len)
        {
            break;
        }

        std::string transition = backbone.substr(i, g);
        e = new Edge(transition);
        
        std::vector<Edge*> neighbours;
        neighbours.push_back(e);
        _graph[*n] = neighbours;
        i += (g - k);
    }
}

std::map<Node, std::vector<Edge*> > KmerGraph::getGraph()
{
    return _graph;
}

void KmerGraph::addSequence(Sequence s)
{

}