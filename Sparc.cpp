#include <iostream>
#include "Sequence.h"
#include "backbone.h"
#include "KmerGraph.h"
#include "Node.h"
#include "Edge.h"

int main()
{
    std::string pathToAlignments = "consensus_input/lambda_alignments_cigar.sam"; // path to location folder of the alignments.sam file
    std::cout << "Extracting sequences started from file: '" + pathToAlignments + "'"<< std::endl;
    Sequence::extractSequences(pathToAlignments);
    std::cout << "\nFinished! Exiting..." << std::endl;
    Backbone* bb = Backbone::createFromFile("consensus_input/lambda_layout.fasta");
    KmerGraph *graph = new KmerGraph(bb, 2, 3);

    Sequence *sequence = Sequence::loadFromFile("/Users/domagoj/programiranje/sparc/sequence_alignments/5.txt");
    std::cout << bb->value.substr(sequence->getBackboneIndex() - 1).substr(0, 100) << std::endl;
    graph->addSequence(sequence);

    return 0;
}