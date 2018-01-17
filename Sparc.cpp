#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <fstream>
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

    std::string pathToAlignments = "consensus_input/lambda_alignments_cigar.sam"; // path to location folder of the alignments.sam file
    std::cout << "Extracting sequences started from file: '" + pathToAlignments + "'"<< std::endl;
    Sequence::extractSequences(pathToAlignments);

    Backbone* bb = Backbone::createFromFile("consensus_input/lambda_layout.fasta");
    KmerGraph *graph = new KmerGraph(bb, 2, 3);

    std::string folder = "sequence_alignments";
    
    int count = 0;
    DIR* dirp = opendir(folder.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) 
    {
        std::string f = folder + "/" + (dp->d_name);
        // std::cout << "File: " << f << "\n" << std::endl;
        if(f.substr(f.length() - 3) == "txt")
        {
            Sequence *sequence = Sequence::loadFromFile(f);
            graph->addSequence(sequence);    
            count++;
   
        }
    }
    closedir(dirp);

    std::cout << "\nNumber of files read: " << count << "\n" << std::endl;

    TopologicalSortSearch *tss = new TopologicalSortSearch(graph);
    std::pair<std::string, int> solution = tss->run();
    std::string path = solution.first;
    float weight = solution.second;

    std::ofstream outputFile;
    outputFile.open ("consensus_input/lambda_results.fasta");
    outputFile << "<"<<std::to_string(weight)<<"\n";
    outputFile << path;
    outputFile.close();
    return 0;

    return 0;
}