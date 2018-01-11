#include <iostream>
#include "Sequence.h"
#include "backbone.h"
#include "KmerGraph.h"
#include "Node.h"
#include "Edge.h"

int main()
{
    std::cout << "Hello!" << std::endl;
    // Sequence::extractSequences(); 
    // Sequence* s = Sequence::loadFromFile("/home/luka/Workspaces/C++/sparc/sequence_alignments/1.txt"); 
    // std::cout << s->getCigarSequence(); 
    Backbone* bb = Backbone::createFromFile("/Users/domagoj/Downloads/consenus_input/lambda_layout.fasta");
    KmerGraph *graph = new KmerGraph(bb, 2, 3);
    
    Node *n = new Node(0, "AA");
    std::vector<Edge> edges =  graph->getGraph()[*n];

    std::cout << edges[0].transition << std::endl;
    std::string bla = edges[0].endNode->getKmer();
    std::cout << bla << std::endl;
    
    return 0;
}