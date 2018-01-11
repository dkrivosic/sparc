#include <iostream>
#include "Sequence.h"
#include "backbone.h"

int main()
{
    std::string pathToAlignments = "sparc/consenus_input/lambda_alignments_cigar.sam"; // path to location folder of the alignments.sam file
    std::cout << "Extracting sequences started from file: '" + pathToAlignments + "'"<< std::endl;
    Sequence::extractSequences(pathToAlignments);
    std::cout << "\nFinished! Exiting..." << std::endl;
    Backbone* bb = Backbone::createFromFile("/Users/mislav/Desktop/consenus_input/lambda_layout.fasta");
    std::cout << bb->value;
    return 0;
}