#include "TopologicalSortSearch.h"
#include "Node.h"
#include "Edge.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <vector>


TopologicalSortSearch::TopologicalSortSearch(std::map<Node, std::vector<Edge*> > graph)
{
    this->graph = graph;
}

std::map<Node, std::vector<Edge*> > TopologicalSortSearch::createGraph()
{
    const int inf = -1;
    int n = 12;
    std::vector<std::pair<int, int> > vi; 
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

std::pair<std::string, int> TopologicalSortSearch::run()
{
    reverse();
    std::cout<<"-----------------------------------------------------"<<std::endl;
    reverse();
    std::cout<<"-----------------------------------------------------"<<std::endl;
    reverse();
    // reverse();
    // std::vector<int> sorted = sort();

    // int numberOfVertices = graph.size();

    // for(int i=0; i<numberOfVertices; i++) {
    //     int vertex = sorted[i];
        // std::cout << vertex << ' ';
    // }
    // return search(sorted);
    return std::make_pair("aaa", 0);
}

// std::pair<std::string, int> TopologicalSortSearch::search(std::vector<int> sorted) {
    // int numberOfVertices = graph.size();
    // int last = sorted[numberOfVertices-1];
    // std::vector<int> distances(numberOfVertices, -1);
    // distances[last] = 0;
    // std::vector<int> path(numberOfVertices, -1);

    
    // for(int i=numberOfVertices-1; i>=0; i--) {
    //     int vertex = sorted[i];
        // cout << "start: " << x <<endl;
        // cout << distances[x] <<endl;
        // if(distances[vertex]==-1){
        //     continue;
        // }
        // for(int j=0; j<graph[vertex].size(); j++) {
        //     std::pair<int, int> node = graph[vertex][j];
        //     int neighbour = node.first;
        //     int dist = node.second;
            // cout << "N :" << vertex <<endl;
            //  cout << "D:" << dist <<endl;
            // if(distances[neighbour] < distances[vertex]+dist) {
            //     distances[neighbour] = distances[vertex]+dist;
            //     path[neighbour] = vertex;
            // }
        //  }    
    // }
    // std::cout<<std::endl;
    // for(int i=0; i<numberOfVertices; i++) {
    //     int x = distances[i];
    //     std::cout << x << ' ';
    //  }
    //  std::cout<<std::endl;
    
    // std::string solution = "";
    // int node = sorted[0];
    // std::cout<<node <<std::endl;
    // std::cout<<current<<std::endl;
    // while(node!=-1) {
    //     solution += "->";
    //     solution += std::to_string(node);
    //     node = path[node];
    // }
    // std::cout<<std::endl<<' ';
    // for(int i=0; i<numberOfVertices; i++) {
    //     int vertex = path[i];
        // std::cout<<vertex<<' ';
       
    // }
    // return std::make_pair(solution.substr(2, solution.size()-2), distances[node]);

// }

void TopologicalSortSearch::reverse()
{
    std::map<Node, std::vector<Edge*> > reversed;
    std::map<Node, bool> visited;

    for (auto const& element : this->graph){
        Node node = element.first;
        std::vector<Edge*> edges = element.second;
        std::cout<<"V: "<< node.kmer<<std::endl;
        int numberOfNeighbours = edges.size();
        std::cout<<"susjedi : "<<numberOfNeighbours<<std::endl;

        if(!visited.count(node)) {
            visited[node] = false;
        }
        for(int j=0; j<numberOfNeighbours; j++) {
            Edge *e = edges[j];
            Node *n = e->endNode;
            int weight = e->weight;
            std::cout<<"N: "<< n->kmer<<std::endl;
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

// void TopologicalSortSearch::put(int vertex)
// {
    // if(called[vertex]) {
    //       exit(-1);
    // }
    // called[vertex] = true;
    // int numberOfNeighbours = graph[vertex].size();

    // // std::cout<< "V : "<< vertex <<std::endl;

    // for(int i=0; i<numberOfNeighbours; i++) {
    //     std::pair<int, int> node = graph[vertex][i];
    //     int neighbour = node.first;
    //     // std::cout<< "N : "<< vertex <<std::endl;
    //     if(!visited[neighbour]) {
    //         put(neighbour);
    //     }
    // }
    // // std::cout<<std::endl;
    // // std::cout<< "A : "<< vertex <<std::endl;
    // sorted.push_back(vertex);
    // called[vertex] = false;
    // visited[vertex] = true;
   
// }
    

// std::vector<int> TopologicalSortSearch::sort()
// {
    // int numberOfVertices = graph.size();
    // for(int vertex=0; vertex<numberOfVertices; vertex++) {
    //     if(!visited[vertex]){
    //         put(vertex);
    //     }
    // }
    // return this->sorted;
// }
    