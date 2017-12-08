#include <string>
#include "sequence.h"
#include "backbone.h"

class KmerGraph
{
    private:
        void initializeGraph(std::string);
        // TODO: graph
    public:
        KmerGraph(Backbone);
        ~KmerGraph();
        void addSequence(Sequence);
        // TODO: getGraph()


};