#include "Sequence.h"
#include "backbone.h"
#include "Node.h"
#include "Edge.h"
#include <string>
#include <map>
#include <vector>

class KmerGraph
{
    private:
        void initializeGraph(std::string);
        std::map<Node, std::vector<Edge> > _graph;
        int k, g;
    public:
        KmerGraph(Backbone*, int, int);
        ~KmerGraph();
        void addSequence(Sequence);
        std::map<Node, std::vector<Edge> > getGraph();
        // Node initialNode;


};