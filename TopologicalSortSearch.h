#pragma once
#include <string>
#include <vector>

class TopologicalSortSearch
{
    public:
        std::vector<std::vector<std::pair<int, int> > > graph;
        TopologicalSortSearch(std::vector<std::vector<std::pair<int, int> > >);
        std::string run();
    private :
        void reverse();
};