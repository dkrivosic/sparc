#include "TopologicalSortSearch.h"
#include <cstdlib>
#include <iostream>

TopologicalSortSearch::TopologicalSortSearch(std::vector<std::vector<std::pair<int, int> > > graph)
{
    this->graph = graph;
}

std::pair<std::string, int> TopologicalSortSearch::run()
{
    // reverse();
    std::vector<int> sorted = sort();

    int numberOfVertices = graph.size();

    for(int i=0; i<numberOfVertices; i++) {
        int vertex = sorted[i];
        // std::cout << vertex << ' ';
    }
    return search(sorted);
}

std::pair<std::string, int> TopologicalSortSearch::search(std::vector<int> sorted) {
    int numberOfVertices = graph.size();
    int last = sorted[numberOfVertices-1];
    std::vector<int> distances(numberOfVertices, -1);
    distances[last] = 0;
    std::vector<int> path(numberOfVertices, -1);

    
    for(int i=numberOfVertices-1; i>=0; i--) {
        int vertex = sorted[i];
        // cout << "start: " << x <<endl;
        // cout << distances[x] <<endl;
        if(distances[vertex]==-1){
            continue;
        }
        for(int j=0; j<graph[vertex].size(); j++) {
            std::pair<int, int> node = graph[vertex][j];
            int neighbour = node.first;
            int dist = node.second;
            // cout << "N :" << vertex <<endl;
            //  cout << "D:" << dist <<endl;
            if(distances[neighbour] < distances[vertex]+dist) {
                distances[neighbour] = distances[vertex]+dist;
                path[neighbour] = vertex;
            }
         }    
    }
    // std::cout<<std::endl;
    // for(int i=0; i<numberOfVertices; i++) {
    //     int x = distances[i];
    //     std::cout << x << ' ';
    //  }
    //  std::cout<<std::endl;
    
    std::string solution = "";
    int node = sorted[0];
    // std::cout<<node <<std::endl;
    // std::cout<<current<<std::endl;
    while(node!=-1) {
        solution += "->";
        solution += std::to_string(node);
        node = path[node];
    }
    // std::cout<<std::endl<<' ';
    for(int i=0; i<numberOfVertices; i++) {
        int vertex = path[i];
        // std::cout<<vertex<<' ';
       
    }
    return std::make_pair(solution.substr(2, solution.size()-2), distances[node]);

}

void TopologicalSortSearch::reverse()
{
    std::vector<std::vector<std::pair<int, int> > > reversed; 
    std::vector<std::pair<int, int> > vi; 
    int numberOfVertices = graph.size();
    reversed.insert(reversed.begin(), numberOfVertices, vi);
    for(int i=0; i<numberOfVertices; i++) {
        int numberOfNeighbours = graph[i].size();
        // std::cout<<"V: "<<i << ' '<<std::endl;
        for(int j=0; j<numberOfNeighbours; j++) {
            std::pair<int, int> node = graph[i][j];
            // std::cout<<node.first << ' ';
            int vertex = node.first;
            int weight = node.second;
            reversed[vertex].push_back(std::make_pair(i, weight));  
        }
        // std::cout<<std::endl;
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

    // std::cout<< "V : "<< vertex <<std::endl;

    for(int i=0; i<numberOfNeighbours; i++) {
        std::pair<int, int> node = graph[vertex][i];
        int neighbour = node.first;
        // std::cout<< "N : "<< vertex <<std::endl;
        if(!visited[neighbour]) {
            put(neighbour);
        }
    }
    // std::cout<<std::endl;
    // std::cout<< "A : "<< vertex <<std::endl;
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
    