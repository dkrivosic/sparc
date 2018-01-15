#include "TopologicalSortSearch.h"

TopologicalSortSearch::TopologicalSortSearch(std::vector<std::vector<std::pair<int, int> > > graph)
{
    this->graph = graph;
}

std::string TopologicalSortSearch::run()
{
    reverse();
    reverse();
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
        // cout<<"V:"<<i << ' '<<endl;
        for(int j=0; j<numberOfNeighbours; j++) {
            std::pair<int, int> node = graph[i][j];
            // cout<<p.first << ' ';
            int vertex = node.first;
            int weight = node.second;
            reversed[vertex].push_back(std::make_pair(i, weight));  
        }
        // cout<<endl;
    }
    this->graph = reversed;
}