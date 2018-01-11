#include <iostream>
#include "Sequence.h"
#include "backbone.h"

int main()
{
    std::cout << "Hello!" << std::endl;
    Sequence::extractSequences(); 
    Sequence* s = Sequence::loadFromFile("/home/luka/Workspaces/C++/sparc/sequence_alignments/1.txt"); 
    std::cout << s->getCigarSequence(); 
    Backbone* bb = Backbone::createFromFile("/Users/mislav/Desktop/consenus_input/lambda_layout.fasta");
    std::cout << bb->value;
    return 0;
}