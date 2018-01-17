#include "TopologicalSortSearch.h"
#include "Node.h"
#include "Edge.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <vector>


TopologicalSortSearch::TopologicalSortSearch(KmerGraph *graph)
{
    this->graph = graph->getGraph();
    this->initial = graph->initialNode;
}

std::pair<std::string, float> TopologicalSortSearch::run()
{
    reverse();
    std::vector<Node> sorted = sort();
    int numberOfVertices = sorted.size();
    return search(sorted);
}

std::pair<std::string, float> TopologicalSortSearch::search(std::vector<Node> sorted) {
    std::map<Node, float> distances;
    std::map<Node, Node*> path;
    std::map<Node, float>::iterator it;
    std::map<Node, Node*>::iterator iter;

    int numberOfVertices = sorted.size();
    Node last = sorted[numberOfVertices-1];
    distances[last] = 0;

    
    for(int i=numberOfVertices-1; i>=0; i--)
    {
        Node node = sorted[i];

        it = distances.find(node);
        if (it == distances.end())
        {
            continue;
        }
        std::vector<Edge*> edges = this->graph[node];
        int numberOfNeighbours = edges.size();

        for(int j=0; j<numberOfNeighbours; j++)
        {
            Edge *e = edges[j];
            Node *n = e->endNode;
            float weight = e->weight;

            if(distances[*n] < distances[node]+weight)
            {
                distances[*n] = distances[node]+weight;
                path[*n] = new Node(node.backboneIndex, node.kmer);
            }
         }    
    }
    
    Node node = *this->initial;
    iter = path.find(node);
    float distance = distances[node];
    std::string solution = node.kmer;  

    reverse();

    while(iter != path.end())
    {
        std::vector<Edge*> edges = this->graph[node];
        int numberOfNeighbours = edges.size();
        for(int i=0; i<numberOfNeighbours; i++)
        {
            Edge *e = edges[i];
            Node *n = e->endNode;
            if(*n==*path[node])
            {
                solution+=e->transition;
                break;
            }
        }
        node=*path[node]; 
        iter = path.find(node);
    }
    return std::make_pair(solution, distance);
}

void TopologicalSortSearch::reverse()
{
    std::map<Node, std::vector<Edge*> > reversed;
    std::map<Node, bool> visited;

    for (auto const& element : this->graph)
    {
        Node node = element.first;
        std::vector<Edge*> edges = element.second;
        int numberOfNeighbours = edges.size();
        if(!visited.count(node))
        {
            visited[node] = false;
        }
        for(int j=0; j<numberOfNeighbours; j++)
        {
            Edge *e = edges[j];
            Node *n = e->endNode;
            float weight = e->weight;
            Edge *eReversed = new Edge(e->transition);
            eReversed->endNode = new Node(node.backboneIndex,node.kmer);
            eReversed->weight = weight;

            if(reversed.count(*n))
            {
                 reversed[*n].push_back(eReversed);
            }
            else{
                std::vector<Edge*> temp;
                temp.push_back(eReversed);
                reversed[*n] = temp;
            }
            visited[*n] = true;
        }
    } 

    for (auto const& element : visited)
    {
        Node node = element.first;
        bool isVisited = element.second; 
        if(!isVisited)
        {
            std::vector<Edge*> temp;
            reversed[node] = temp;
        }
    }
    this->graph = reversed;  
}

void TopologicalSortSearch::put(Node node)
{
    std::map<Node, bool>::iterator it;
    it = called.find(node);
    if(it != called.end())
    {
        exit(-1);      
    }
    called[node] = true;

    std::vector<Edge*> edges = this->graph[node];
    int numberOfNeighbours = edges.size();

    for(int i=0; i<numberOfNeighbours; i++)
    {
        Edge *e = edges[i];
        Node *n = e->endNode;
        it = visited.find(*n);
        if (it == visited.end())
        {
             put(*n);
        }
    }
    sorted.push_back(node);
    called.erase(node);
    visited[node] = true;
   
}
    

std::vector<Node> TopologicalSortSearch::sort()
{
    
    for (auto const& element : this->graph)
    {
        Node node = element.first;
        std::map<Node, bool>::iterator it = visited.find(node);
        if (it == visited.end())
        {
             put(node);
        }
    }
    return this->sorted;
}
    