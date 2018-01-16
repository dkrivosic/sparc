#include <iostream>
#include "Sequence.h"
#include "backbone.h"
#include "KmerGraph.h"
#include "Node.h"
#include "Edge.h"
#include "TopologicalSortSearch.h"

int main()
{

    std::string pathToAlignments = "consensus_input/lambda_alignments_cigar.sam"; // path to location folder of the alignments.sam file
    std::cout << "Extracting sequences started from file: '" + pathToAlignments + "'"<< std::endl;
    Sequence::extractSequences(pathToAlignments);
    std::cout << "\nFinished! Exiting..." << std::endl;
    Backbone* bb = Backbone::createFromFile("consensus_input/lambda_layout.fasta");
    KmerGraph *graph = new KmerGraph(bb, 2, 3);

    Sequence *sequence = Sequence::loadFromFile("sequence_alignments/5.txt");
    
    graph->addSequence(sequence);

    TopologicalSortSearch *tss = new TopologicalSortSearch(graph->getGraph());
    std::pair<std::string, int> solution = tss->run();
    std::string path = solution.first;
    int weight = solution.second;

    std::cout<<path << std::endl;
    std::cout<<weight << std::endl;
    return 0;
}