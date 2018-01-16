#pragma once
#include <string>
#include <vector>
#include <map>
#include "Node.h"
#include "Edge.h"


class TopologicalSortSearch
{
    public:
        std::map<Node, std::vector<Edge*> > graph;
        TopologicalSortSearch(std::map<Node, std::vector<Edge*> >);
        std::pair<std::string, float>  run();
        static std::map<Node, std::vector<Edge*> > createGraph();
    private :
        void reverse();
        void put(Node node);
        std::pair<std::string, float> search(std::vector<Node>);
        std::vector<Node> sort();
        std::vector<Node> sorted;
        std::map <Node, bool> visited;
        std::map<Node, bool> called;
};