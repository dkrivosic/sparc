#pragma once
#include <string>
#include <vector>
#include <map>
#include "Node.h"
#include "Edge.h"


class TopologicalSortSearch
{
    public:
        std::vector<std::vector<std::pair<int, int> > > graph;
        TopologicalSortSearch(std::vector<std::vector<std::pair<int, int> > >);
        std::pair<std::string, int>  run();
        static std::map<Node, std::vector<Edge*> > createGraph();
    private :
        void reverse();
        void put(int vertex);
        std::pair<std::string, int> search(std::vector<int>);
        std::vector<int> sort();
        std::vector<int> sorted;
        std::map <int, bool> visited;
        std::map<int, bool> called;
};