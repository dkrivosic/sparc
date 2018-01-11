#include <iostream>
#include "Sequence.h"

int main()
{
    std::cout << "Hello!" << std::endl;
    Sequence::extractSequences();
    Sequence* s = Sequence::loadFromFile("/home/luka/Workspaces/C++/sparc/sequence_alignments/1.txt");
    std::cout << s->getCigarSequence();
    return 0;
}