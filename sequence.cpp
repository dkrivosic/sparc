#include "sequence.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <vector>

Sequence::Sequence(int bIndex, int seqIndex, std::string seq) {
    backboneIndex = bIndex;
    sequenceIndex = seqIndex;
    sequence = seq;
}

static Sequence createFromFile() {
    // create folder for sequence files 
    system("mkdir /home/luka/Workspaces/C++/sparc/sequence_alignments");
    
    // open alignments SAM file created GraphMap with CIGAR syntax
    std::string line;
    std::ifstream alignmentsFile;
    alignmentsFile.open ("/home/luka/Workspaces/C++/sparc/consenus_input/lambda_alignments_cigar.sam");

    if (alignmentsFile.is_open()){
        std::vector<std::string> tokens;
        std::stringstream stringToInt;
        while (!alignmentsFile.eof){
            // read the line from the file
            getline(alignmentsFile, line);
            
            // split it by tab character
            tokens = split (line, '\t');

            // create Sequence object
            int backboneIndexInt = 0;
            stringToInt >> tokens[3];
            int sequenceIndexInt = 0;
            stringToInt >> tokens[0];
            Sequence seq (backboneIndexInt, sequenceIndexInt, tokens[5]);

            // save to file
        }
    } else {
        std::cout << "File is not opened. Exiting...";
        exit(1);
    }
    
    // close alignments file
    alignmentsFile.close();
}

void Sequence::saveToFile(std::string saveLocation){
    int index = getsequenceIndex();
    std::string filePath = saveLocation + std::to_string(index) + ".txt";
    std::ofstream ofsSaveSequence(filePath.c_str());
    ofsSaveSequence << backboneIndex << std::endl <<sequenceIndex << std::endl << sequence;
}

Sequence Sequence::loadFromFile(std::string loadLocation, std::string index){
    std::string loadPath = loadLocation + index + ".txt";
    std::ifstream ifsLoadSequence(loadPath.c_str());
    ifsLoadSequence >> backboneIndex >> sequenceIndex >> sequence;
     // create object and return
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}