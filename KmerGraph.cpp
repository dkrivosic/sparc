#include "KmerGraph.h"
#include "Node.h"
#include "Edge.h"
#include "backbone.h"
#include <string>
#include <map>
#include <vector>
#include <set>

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

void KmerGraph::addSequence(Sequence *s)
{
    std::string sequence = s->getSequence();
    std::string cigar_sequence = s->getCigarSequence();
    
    char symbols[] = { 'I', 'D', 'X', '=', 'S', 'N', 'H', 'P' };

    int seqIndex = 0;
    int cigarIndex = 0;
    int backboneIndex = s->getBackboneIndex() - 1;

    std::string result = "";
    std::string cigar = "";

    for (int i = 0; i < cigar_sequence.length(); i++)
    {
        bool isSymbol = false;
        for (char symbol : symbols)
        {
            if (cigar_sequence[i] == symbol)
            {
                isSymbol = true;
            }
        }
        if (isSymbol)
        {
            int number = std::stoi(cigar_sequence.substr(cigarIndex, i - cigarIndex));
            char action = cigar_sequence[i];
            cigarIndex = i + 1;
            
            // Do action
            for (int j = 0; j < number; j++)
            {
                if (action == 'D')
                {
                    result += "-";
                    cigar += action;
                }
                else if (action == '=' || action == 'X' || action == 'M')
                {
                    result += sequence[seqIndex];
                    cigar += action;
                    seqIndex++;
                }
                else if (action == 'I')
                {
                    seqIndex++;
                }
                else if (action == 'S' || action == 'H')
                {
                    seqIndex++;
                }
            }
        }
    }

    // Find index of the first node after backbone index
    int i = 0;
    while ((backboneIndex + i) % g != 0) i++;

    // Find first common node between backbone and sequence
    Node *n = nullptr;
    while (true)
    {
        Node *tmp = new Node(backboneIndex + i, sequence.substr(i, k));
        if (_graph.find(*tmp) != _graph.end())
        {
            n = tmp;
            break;
        }
        i += g;
    }

    int len = sequence.length();
    Edge *e = nullptr;
    while (i <= len - 1)
    {
        i += k;
        if (i >= len) break;
        std::string transition = sequence.substr(i, g);
        i += (g - k);
        if (i >= len) break;
        std::string kmer = sequence.substr(i, k);
        Node *endNode = new Node(backboneIndex + i, kmer);
        e = new Edge(transition, endNode);

        if (_graph.find(*n) != _graph.end())
        {
            bool found = false;
            for (int j = 0; j < _graph[*n].size(); j++)
            {
                if (_graph[*n][j] == e)
                {
                    _graph[*n][j]->weight += 1;
                    found = true;
                }
            }
            if (!found)
            {
                _graph[*n].push_back(e);
            }
        }
        else
        {
            std::vector<Edge*> neighbours;
            neighbours.push_back(e);
            _graph[*n] = neighbours;
        }

        n = endNode;
    }

    std::cout << result.substr(0, 100) << std::endl; 
    std::cout << cigar.substr(0, 100) << std::endl;

}