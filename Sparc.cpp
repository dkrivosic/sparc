#include <iostream>
#include "Sequence.h"
#include "backbone.h"
#include "KmerGraph.h"
#include "Node.h"
#include "Edge.h"
#include "TopologicalSortSearch.h"

const int inf = -1;
int n = 12;

int main()
{
    std::vector<std::vector<std::pair<int, int> > > graph;
    TopologicalSortSearch *tss = new TopologicalSortSearch(graph);
    std::string output = tss->run();
    std::cout<<output;


    // std::string pathToAlignments = "consensus_input/lambda_alignments_cigar.sam"; // path to location folder of the alignments.sam file
    // std::cout << "Extracting sequences started from file: '" + pathToAlignments + "'"<< std::endl;
    // Sequence::extractSequences(pathToAlignments);
    // std::cout << "\nFinished! Exiting..." << std::endl;
    // Backbone* bb = Backbone::createFromFile("consensus_input/lambda_layout.fasta");
    // std::cout << bb->value;
    return 0;
}