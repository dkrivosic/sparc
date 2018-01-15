#pragma once
#include <string>
#include <vector>
#include <map>

class TopologicalSortSearch
{
    public:
        std::vector<std::vector<std::pair<int, int> > > graph;
        TopologicalSortSearch(std::vector<std::vector<std::pair<int, int> > >);
        std::string run();
    private :
        void reverse();
        void put(int vertex);
        std::vector<int> sort();
        std::vector<int> sorted;
        std::map <int, bool> visited;
        std::map<int, bool> called;
};