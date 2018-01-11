#include "KmerGraph.h"
#include "Node.h"
#include "Edge.h"
#include <string>
#include <map>
#include <vector>

KmerGraph::KmerGraph(Backbone backbone, int k = 2, int g = 3)
{
    // initializeGraph(backbone.value);
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

        i += k;
        if (i >= len)
        {
            break;
        }

        std::string transition = backbone.substr(i, g);
        e = new Edge(transition);
        
        std::vector<Edge> neighbours;
        neighbours.push_back(*e);
        _graph[*n] = neighbours;

        i += (g - k);
    }
}