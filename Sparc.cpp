#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <typeinfo>
#include "Sequence.h"
#include "backbone.h"
#include "KmerGraph.h"
#include "Node.h"
#include "Edge.h"
#include "TopologicalSortSearch.h"

// std::map<Node, std::vector<Edge*> > graphBFS;
// std::map<Node, std::vector<Edge*> > graphCalc;

// void bfs(Node node) {
//     std::vector<Edge*> edges = graphCalc[node].

// }

int main()
{

    Backbone* bb = Backbone::createFromFile("consensus_input/lambda_layout.fasta");
    KmerGraph *graph = new KmerGraph(bb, 2, 3);

    std::string pathToAlignments = "consensus_input/lambda_alignments_cigar.sam"; // path to location folder of the alignments.sam file
    std::cout << "Extracting sequences started from file: '" + pathToAlignments + "'"<< std::endl;

    // 

    std::string line;
    std::ifstream alignmentsFile(pathToAlignments);

    if (alignmentsFile.is_open())
    {
        std::istringstream iss;
        int backboneIndexInt;
        int sequenceIndexInt;
        std::string cigarSequence;
        std::string sequence;
        int count = 0;

        for(int i = 0; i < 3; i++)
        {
            getline(alignmentsFile, line);
        }

        while(getline(alignmentsFile, line))
        {
            count++;
            iss.str(line);
            std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>());

            sequenceIndexInt = stoi(results[0]);
            backboneIndexInt = stoi(results[3]);
            cigarSequence = results[5];
            sequence = results[9];
            
            if(sequenceIndexInt % 100 == 0)
            {
                std::cout << "Progress: " << count << std::endl; 
            }

            if(backboneIndexInt != 0)
            {
                Sequence *seq = new Sequence(sequenceIndexInt, backboneIndexInt,cigarSequence, sequence);
                graph->addSequence(seq);    
            }
            
            iss.clear();
            cigarSequence.clear();
            sequence.clear();
        }
    }
    else
    {
        std::cout << "File is not opened. Exiting...";
        exit(1);
    }
    
    // close alignments file
    alignmentsFile.close();

    // 

    TopologicalSortSearch *tss = new TopologicalSortSearch(graph);
    std::pair<std::string, int> solution = tss->run();
    std::string path = solution.first;
    float weight = solution.second;
    // std::cout << path << std::endl;

    std::ofstream outputFile;
    outputFile.open ("consensus_input/lambda_results.fasta");
    outputFile << ">"<<std::to_string(weight)<<"\n";
    outputFile << path;
    outputFile.close();
    return 0;
// 
    // return 0;
}