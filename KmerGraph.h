#include "sequence.h"
#include "backbone.h"
#include "kmer.h"
#include <string>
#include <map>
#include <vector>

class KmerGraph
{
    private:
        void initializeGraph(std::string);
        std::map<std::string, std::vector<std::string, int> > _graph;
    public:
        KmerGraph(Backbone, int, int);
        ~KmerGraph();
        void addSequence(Sequence);
        // TODO: getGraph()


};