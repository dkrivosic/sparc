#include "KmerGraph.h"
#include "Node.h"
#include "Edge.h"
#include "backbone.h"
#include "Insert.h"
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
    this->backbone = backbone;
    initializeGraph(backbone->value);
}

KmerGraph::~KmerGraph()
{

}

int KmerGraph::firstNodeBefore(int index)
{
    index -= k;
    while (index >= 0)
    {
        if (index % this->g == 0)
        {
            return index;
        }
        index--;
    }
    return -1;
}

int KmerGraph::firstNodeAfter(int index)
{
    while (index < this->backbone->value.length())
    {
        if (index % this->g == 0)
        {
            return index;
        }
        index++;
    }
    return -1;
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

    std::set<Insert*> inserts;

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
            if (action == 'D')
            {
                for (int j = 0; j < number; j++)
                {
                    result += "-";
                    cigar += action;
                    backboneIndex++;
                }
            }
            else if (action == '=' || action == 'X' || action == 'M')
            {
                for (int j = 0; j < number; j++)
                {
                    result += sequence[seqIndex];
                    cigar += action;
                    seqIndex++;
                    backboneIndex++;
                }
            }
            else if (action == 'I')
            {
                std::string insertString = sequence.substr(seqIndex, number);
                int startNodeIndex = firstNodeBefore(backboneIndex);
                int endNodeIndex = firstNodeAfter(backboneIndex);
                
                if (startNodeIndex > -1 && endNodeIndex > -1)
                {
                    std::string startNodeKmer = this->backbone->value.substr(startNodeIndex, k);
                    Node *startNode = new Node(startNodeIndex, startNodeKmer);
                    std::string endNodeKmer = this->backbone->value.substr(endNodeIndex, k);
                    Node *endNode = new Node(endNodeIndex, endNodeKmer);
                    std::string graphString = this->backbone->value.substr(startNodeIndex + k, endNodeIndex - startNodeIndex - k);
                    int insertIndex = backboneIndex - startNodeIndex - k;
                    Insert *insert = new Insert(startNode, endNode, graphString, insertString, insertIndex);
                    inserts.insert(insert);
                }
                seqIndex += number;

            }
            else if (action == 'S' || action == 'H')
            {
                seqIndex += number;
                backboneIndex += number;
            }
        }
    }

    // Find index of the first node after backbone index
    int i = 0;
    while ((s->getBackboneIndex() + i) % g != 0) i++;

    // Find first common node between backbone and sequence
    Node *n = nullptr;
    while (true)
    {
        Node *tmp = new Node(s->getBackboneIndex() + i, sequence.substr(i, k));
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
        Node *endNode = new Node(s->getBackboneIndex() + i, kmer);
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

    std::cout << this->backbone->value.substr(s->getBackboneIndex() - 1).substr(100, 50) << std::endl;
    std::cout << result.substr(100, 50) << std::endl; 
    std::cout << cigar.substr(100, 50) << std::endl;

    // Do inserts
    for (Insert* insert : inserts)
    {
        std::vector<Edge*> edges;
        std::string newSequence = insert->graphString.substr(0, insert->index) + insert->insertString + insert->graphString.substr(insert->index);
        std::cout << insert->startNode->backboneIndex << " " << insert->startNode->kmer << " " << newSequence << " " << insert->endNode->kmer << " " << insert->insertString << std::endl;
        int edgesCount = newSequence.length() % g + 1;
        int j = 0;
        for (int i = 0; i < edgesCount; i++)
        {
            if (j >= newSequence.length())
            {
                j -=g;
                break;
            }
            // TODO: dodaj string ID-jeve
            std::string nodeKmer = newSequence.substr(j + g - k, k);
            std::string edgeString = newSequence.substr(j, g);
            Node *n = new Node(-1, nodeKmer);
            Edge *e = new Edge(edgeString, n);
            edges.push_back(e);
            j += g;
        }

        if (j < newSequence.length())
        {
            std::string edgeString = newSequence.substr(j);
            Edge *e = new Edge(edgeString, insert->endNode);
        }

        // TODO: ubaci u graf
    }

}