#include <iostream>
#include "Sequence.h"
#include "backbone.h"
#include "KmerGraph.h"
#include "Node.h"
#include "Edge.h"
#include "TopologicalSortSearch.h"

const int inf = -1;
int n = 12;

std::vector<std::vector<std::pair<int, int> > > createGraph() {
    std::vector<std::pair<int, int> > vi; 
    std::vector<std::vector<std::pair<int, int> > > graph;
    graph.insert(graph.begin(), n, vi);
    graph[4].push_back(std::make_pair(7, 1));
    graph[2].push_back(std::make_pair(7, 1));
    graph[6].push_back(std::make_pair(1, 1));
    graph[5].push_back(std::make_pair(1, 1));
    graph[3].push_back(std::make_pair(9, 1));
    graph[5].push_back(std::make_pair(3, 2));
    graph[0].push_back(std::make_pair(5, 3));
    graph[10].push_back(std::make_pair(5, 3));
    graph[11].push_back(std::make_pair(5, 3));
    graph[10].push_back(std::make_pair(0, 2));
    graph[11].push_back(std::make_pair(10, 1));
    graph[8].push_back(std::make_pair(4, 2));
    graph[0].push_back(std::make_pair(4, 2));
    graph[8].push_back(std::make_pair(2, 2));
    graph[0].push_back(std::make_pair(2, 2));
    graph[8].push_back(std::make_pair(6, 2));
    graph[10].push_back(std::make_pair(6, 2));
    graph[11].push_back(std::make_pair(6, 2));
    return graph;
}

int main()
{
    std::vector<std::vector<std::pair<int, int> > > graph;
    graph = createGraph();
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