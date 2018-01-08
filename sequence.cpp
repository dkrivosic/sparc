#include "sequence.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>

Sequence::Sequence(int bIndex, int seqIndex, std::string cigar_seq, std::string seq) {
    backboneIndex = bIndex;
    sequenceIndex = seqIndex;
    cigar_sequence = cigar_seq;
    sequence = seq;
}

Sequence Sequence::createFromFile() {
    // create folder for sequence files 
    std::string folder = "/home/luka/Workspaces/C++/sparc/sequence_alignments";

    const int dir_err = system("mkdir -p /home/luka/Workspaces/C++/sparc/sequence_alignments");
    if (-1 == dir_err)
    {
        printf("Error creating directory!n");
        exit(1);
    }
    
    // open alignments SAM file created GraphMap with CIGAR syntax
    std::string line;
    std::ifstream alignmentsFile("/home/luka/Workspaces/C++/sparc/consenus_input/lambda_alignments_cigar.sam");
    // alignmentsFile.open ("/home/luka/Workspaces/C++/sparc/consenus_input/lambda_alignments_cigar.sam");

    if (alignmentsFile.is_open()){
        std::vector<std::string> tokens;
        std::stringstream stringToInt;
        int backboneIndexInt;
        int a;
        std::string b;
        int sequenceIndexInt;
        std::string cigarSequence;
        std::string sequence;
        while (alignmentsFile >> sequenceIndexInt >> a >> b >> backboneIndexInt >> a >> cigarSequence >> sequence >> a >> a >> b >> b >> b >> b >> b >> b >> b >> b >> b >> b){
            
            Sequence::saveToFile(folder, sequenceIndexInt, backboneIndexInt,cigarSequence, sequence);

            /*// read the line from the file
            getline(alignmentsFile, line);
            
            // split it by tab character
            tokens = split (line, '\t');

            // create Sequence object
            int backboneIndexInt = 0;
            stringToInt >> tokens[3];
            int sequenceIndexInt = 0;
            stringToInt >> tokens[0];
            Sequence *seq = new Sequence(backboneIndexInt, sequenceIndexInt, tokens[5]);*/

            // save to file
        }
    } else {
        std::cout << "File is not opened. Exiting...";
        exit(1);
    }
    
    // close alignments file
    alignmentsFile.close();
}

void Sequence::saveToFile(std::string saveLocation, int sequenceIndexInt, int backboneIndexInt,std::string cigarSequence, std::string sequence){
    std::string filePath = saveLocation + std::to_string(sequenceIndexInt) + ".txt";
    std::ofstream ofsSaveSequence(filePath.c_str());
    if (ofsSaveSequence.is_open()){
        ofsSaveSequence << sequenceIndexInt << std::endl << backboneIndexInt << std::endl << cigarSequence << std::endl << sequence;
    }
    ofsSaveSequence.close();
}

Sequence Sequence::loadFromFile(std::string loadLocation, std::string index){
    std::string loadPath = loadLocation + index + ".txt";
    std::string line;
    std::ifstream ifsLoadSequence(loadPath.c_str());
    int backboneIndex;
    int sequenceIndex;
    std::string cigarSequence;
    std::string sequence;
    if (ifsLoadSequence.is_open()){
        ifsLoadSequence >> backboneIndex >> sequenceIndex >> cigarSequence >> sequence;
        /*ifsLoadSequence >> backboneIndex;
        ifsLoadSequence >> sequenceIndex;
        ifsLoadSequence >> sequence;*/
        ifsLoadSequence.close();
    }
     // create object and return it
    Sequence *seq = new Sequence(backboneIndex, sequenceIndex, cigarSequence, sequence);
}

/*std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}*/