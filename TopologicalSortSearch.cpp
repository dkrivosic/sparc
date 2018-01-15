#include "TopologicalSortSearch.h"
#include <cstdlib>
#include <iostream>

TopologicalSortSearch::TopologicalSortSearch(std::vector<std::vector<std::pair<int, int> > > graph)
{
    this->graph = graph;
}

std::string TopologicalSortSearch::run()
{
    // reverse();
    // reverse();
    std::vector<int> sorted = sort();

    int numberOfVertices = graph.size();
    for(int i=0; i<numberOfVertices; i++) {
        int vertex = sorted[i];
        std::cout << vertex << ' ';
    }

    return "abcdef";
}

void TopologicalSortSearch::reverse()
{
    std::vector<std::vector<std::pair<int, int> > > reversed; 
    std::vector<std::pair<int, int> > vi; 
    int numberOfVertices = graph.size();
    reversed.insert(reversed.begin(), numberOfVertices, vi);
    for(int i=0; i<numberOfVertices; i++) {
        int numberOfNeighbours = graph[i].size();
        // std::cout<<"V:"<<i << ' '<<endl;
        for(int j=0; j<numberOfNeighbours; j++) {
            std::pair<int, int> node = graph[i][j];
            // std::cout<<p.first << ' ';
            int vertex = node.first;
            int weight = node.second;
            reversed[vertex].push_back(std::make_pair(i, weight));  
        }
        // std::std::cout<<endl;
    }
    this->graph = reversed;
}

void TopologicalSortSearch::put(int vertex)
{
    if(called[vertex]) {
          exit(-1);
    }
    called[vertex] = true;
    int numberOfNeighbours = graph[vertex].size();

    std::cout<< "V : "<< vertex <<std::endl;

    for(int i=0; i<numberOfNeighbours; i++) {
        std::pair<int, int> node = graph[vertex][i];
        int neighbour = node.first;
        std::cout<< "N : "<< vertex <<std::endl;
        if(!visited[neighbour]) {
            put(neighbour);
        }
    }
    std::cout<<std::endl;
    std::cout<< "A : "<< vertex <<std::endl;
    sorted.push_back(vertex);
    called[vertex] = false;
    visited[vertex] = true;
   
}
    

std::vector<int> TopologicalSortSearch::sort()
{
    int numberOfVertices = graph.size();
    for(int vertex=0; vertex<numberOfVertices; vertex++) {
        if(!visited[vertex]){
            put(vertex);
        }
    }
    return this->sorted;
}
    