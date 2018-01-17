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


int main(int argc, char** argv)
{
    if(argc < 4)
    {
        std::cout << "Not enough arguments provided..." << std::endl << "Arguments should be: [layout_file] [alignments file] [results_file]" << std::endl;
        exit(-1);
    }

    std::string layout_file = argv[1];
    std::string alignments_file = argv[2];
    std::string results_file = argv[3];

    std::cout << "\nLoading backbone and creating initial graph..." << std::endl;
    Backbone* bb = Backbone::createFromFile(layout_file);
    KmerGraph *graph = new KmerGraph(bb, 2, 3);

    std::cout << "\nExtracting sequences from file: '" + alignments_file + "'"<< " and adding them to the graph...\n" << std::endl;

    std::string line;
    std::ifstream alignmentsFile(alignments_file);

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
                std::cout << "Number of processed files: " << count << std::endl; 
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
    std::cout << "\nGraph created!" << std::endl;

    std::cout << "\nFinding the best path in graph..." << std::endl;
    TopologicalSortSearch *tss = new TopologicalSortSearch(graph);
    std::pair<std::string, int> solution = tss->run();
    std::string path = solution.first;
    float weight = solution.second;

    std::cout << "\nSaving results to file..." << std::endl;
    std::ofstream outputFile;
    outputFile.open (results_file);
    outputFile << ">"<<std::to_string(weight)<<"\n";
    outputFile << path;
    std::cout << "\nSaved!" << std::endl;
    outputFile.close();
    return 0;
}