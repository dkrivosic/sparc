#include "TopologicalSortSearch.h"

TopologicalSortSearch::TopologicalSortSearch(std::vector<std::vector<std::pair<int, int> > > graph)
{
    this->graph = graph;
}

std::string TopologicalSortSearch::run()
{
    return "abcdef";
}