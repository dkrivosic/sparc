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

std::map<Node, std::vector<Edge*> > TopologicalSortSearch::createGraph()
{
    std::map<Node, std::vector<Edge*> > graph;
    
    Node *n0 = new Node(0, "0");
    Node *n1 = new Node(1, "1");
    Node *n2 = new Node(2, "2");
    Node *n3 = new Node(3, "3");
    Node *n4 = new Node(4, "4");
    Node *n5 = new Node(5, "5");
    Node *n6 = new Node(6, "6");
    Node *n7 = new Node(7, "7");
    Node *n8 = new Node(8, "8");
    Node *n9 = new Node(9, "9");
    Node *n10 = new Node(10, "10");
    Node *n11 = new Node(11, "11");

    Edge *e0 = new Edge("0");
    e0->endNode = n4;
    e0->weight = 1.0;
    Edge *e1 = new Edge("1");
    e1->endNode = n2;
    e1->weight = 1.0;
    Edge *e2 = new Edge("2");
    e2->endNode = n6;
    e2->weight = 1.0;
    Edge *e3 = new Edge("3");
    e3->endNode = n5;
    e3->weight = 1.0;
    Edge *e4 = new Edge("4");
    e4->endNode = n3;
    e4->weight = 1.0;
    Edge *e5 = new Edge("5");
    e5->endNode = n8;
    e5->weight = 2.0;
    Edge *e6 = new Edge("6");
    e6->endNode = n0;
    e6->weight = 2.0;
    Edge *e7 = new Edge("7");
    e7->endNode = n8;
    e7->weight = 2.0;
    Edge *e8 = new Edge("8");
    e8->endNode = n8;
    e8->weight = 2.0;
    Edge *e9 = new Edge("9");
    e9->endNode = n0;
    e9->weight = 2.0;
    Edge *e10 = new Edge("10");
    e10->endNode = n10;
    e10->weight = 2.0;
    Edge *e11 = new Edge("11");
    e11->endNode = n11;
    e11->weight = 2.0;
    Edge *e12 = new Edge("12");
    e12->endNode = n5;
    e12->weight = 2.0;
    Edge *e13 = new Edge("13");
    e13->endNode = n0;
    e13->weight = 3.0;
    Edge *e14 = new Edge("14");
    e14->endNode = n10;
    e14->weight = 3.0;
    Edge *e15 = new Edge("15");
    e15->endNode = n11;
    e15->weight = 3.0;
    Edge *e16 = new Edge("16");
    e16->endNode = n10;
    e16->weight = 2.0;
    Edge *e17 = new Edge("17");
    e17->endNode = n11;
    e17->weight = 1.0;
    
    std::vector<Edge*> adjacent;
    adjacent.push_back(e16);
    graph[*n0] = adjacent;
    adjacent.clear();

    adjacent.push_back(e2);
    adjacent.push_back(e3);
    graph[*n1] = adjacent;
    adjacent.clear();

    adjacent.push_back(e7);
    adjacent.push_back(e9);
    graph[*n2] = adjacent;
    adjacent.clear();

    adjacent.push_back(e12);
    graph[*n3] = adjacent;
    adjacent.clear();

    adjacent.push_back(e5);
    adjacent.push_back(e6);
    graph[*n4] = adjacent;
    adjacent.clear();

    adjacent.push_back(e13);
    adjacent.push_back(e14);
    adjacent.push_back(e15);
    graph[*n5] = adjacent;
    adjacent.clear();

    adjacent.push_back(e8);
    adjacent.push_back(e10);
    adjacent.push_back(e11);
    graph[*n6] = adjacent;
    adjacent.clear();

    adjacent.push_back(e0);
    adjacent.push_back(e1);
    graph[*n7] = adjacent;
    adjacent.clear();

    graph[*n8] = adjacent;
    adjacent.clear();

    adjacent.push_back(e4);
    graph[*n9] = adjacent;
    adjacent.clear();

    adjacent.push_back(e17);
    graph[*n10] = adjacent;
    adjacent.clear();

    graph[*n11] = adjacent;
    adjacent.clear();

    return graph;
    
}

std::pair<std::string, float> TopologicalSortSearch::run()
{
    reverse();
    std::vector<Node> sorted = sort();
    int numberOfVertices = sorted.size();
    // for(int i=0; i<numberOfVertices; i++) {
    //     Node node = sorted[i];
    //     std::cout << node.kmer << ' ';
    // }
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

    
    for(int i=numberOfVertices-1; i>=0; i--) {
        Node node = sorted[i];

        it = distances.find(node);
        if (it == distances.end()){
            continue;
        }
        std::vector<Edge*> edges = this->graph[node];
        int numberOfNeighbours = edges.size();

        for(int j=0; j<numberOfNeighbours; j++) {
            Edge *e = edges[j];
            Node *n = e->endNode;
            float weight = e->weight;

            if(distances[*n] < distances[node]+weight) {
                distances[*n] = distances[node]+weight;
                path[*n] = new Node(node.backboneIndex, node.kmer);
            }
         }    
    }
    // std::cout<<std::endl;
    // for (auto const& element : distances){
    //     Node node = element.first;
    //     int distance = element.second;
    //     std::cout<<node.kmer<<" : "<<distance<<std::endl;
    // }
    // std::cout<<std::endl;
    //  for (auto const& element : path){
    //     Node key = element.first;
    //     Node *value = element.second;
    //     std::cout<<key.kmer<<" : "<<value->kmer<<std::endl;
    // }
    
    Node node = *this->initial;
    iter = path.find(node);
    float distance = distances[node];
    std::string solution = node.kmer;  
    reverse();
    while(iter != path.end()) {
        std::vector<Edge*> edges = this->graph[node];
        int numberOfNeighbours = edges.size();
        // std::cout<<"vertex :"<<node.kmer<<std::endl;
        // std::cout<<"susjedi : "<<numberOfNeighbours<<std::endl;

        for(int i=0; i<numberOfNeighbours; i++) {
            Edge *e = edges[i];
            Node *n = e->endNode;
            // std::cout<<"neigh :"<<n->kmer<<std::endl;

            if(*n==*path[node]){
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

    for (auto const& element : this->graph){
        Node node = element.first;
        std::vector<Edge*> edges = element.second;
        // std::cout<<"V: "<< node.kmer<<std::endl;
        int numberOfNeighbours = edges.size();
        // std::cout<<"susjedi : "<<numberOfNeighbours<<std::endl;

        if(!visited.count(node)) {
            visited[node] = false;
        }
        for(int j=0; j<numberOfNeighbours; j++) {
            Edge *e = edges[j];
            Node *n = e->endNode;
            float weight = e->weight;
            // std::cout<<"N: "<< n->kmer<<std::endl;
            Edge *eReversed = new Edge(e->transition);
            eReversed->endNode = new Node(node.backboneIndex,node.kmer);
            eReversed->weight = weight;

            if(reversed.count(*n)) {
                 reversed[*n].push_back(eReversed);
            }
            else {
                std::vector<Edge*> temp;
                temp.push_back(eReversed);
                reversed[*n] = temp;
            }
            visited[*n] = true;
        }
    } 

    for (auto const& element : visited){
        Node node = element.first;
        bool isVisited = element.second; 
        if(!isVisited) {
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
    if(it != called.end()){
        exit(-1);      
    }
    called[node] = true;

    std::vector<Edge*> edges = this->graph[node];
    int numberOfNeighbours = edges.size();

    // std::cout<< "V : "<< node.kmer <<std::endl;

    for(int i=0; i<numberOfNeighbours; i++) {
        Edge *e = edges[i];
        Node *n = e->endNode;
        // std::cout<<"S: "<< n->kmer<<std::endl;
        it = visited.find(*n);
        if (it == visited.end()){
             put(*n);
        }
    }
    // std::cout<<std::endl;
    // std::cout<< "A : "<< vertex <<std::endl;
    sorted.push_back(node);
    called.erase(node);
    visited[node] = true;
   
}
    

std::vector<Node> TopologicalSortSearch::sort()
{
    
    for (auto const& element : this->graph){
        Node node = element.first;
        std::map<Node, bool>::iterator it = visited.find(node);
        if (it == visited.end()){
             put(node);
        }
    }
    return this->sorted;
}
    