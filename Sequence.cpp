#include "Sequence.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

Sequence::Sequence(int bIndex, int seqIndex, std::string cigar_seq, std::string seq) {
    backboneIndex = bIndex;
    sequenceIndex = seqIndex;
    cigar_sequence = cigar_seq;
    sequence = seq;
}

void Sequence::extractSequences() {
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
    std::ifstream alignmentsFile("/home/luka/Workspaces/C++/sparc/consenus_input/lambda_alignments_cigar_1.sam");
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
        while (alignmentsFile >> sequenceIndexInt >> a >> b >> backboneIndexInt >> a >> cigarSequence >> b >> a >> a >> sequence >> b >> b >> b >> b >> b >> b >> b >> b >> b){
            Sequence::saveToFile(folder, sequenceIndexInt, backboneIndexInt,cigarSequence, sequence);
        }
    } else {
        std::cout << "File is not opened. Exiting...";
        exit(1);
    }
    
    // close alignments file
    alignmentsFile.close();
}

void Sequence::saveToFile(std::string saveLocation, int sequenceIndexInt, int backboneIndexInt,std::string cigarSequence, std::string sequence){
    /*std::string Result;
    std::ostringstream convert;
    convert << sequenceIndexInt;
    Result = convert.str();*/
    std::string filePath = saveLocation + "/" + static_cast<std::ostringstream*>( &(std::ostringstream() << sequenceIndexInt) )->str() + ".txt";
    std::ofstream ofsSaveSequence(filePath.c_str());
    if (ofsSaveSequence.is_open()){
        ofsSaveSequence << sequenceIndexInt << " " << backboneIndexInt << " " << cigarSequence << " " << sequence;
    }
    ofsSaveSequence.close();
}

Sequence* Sequence::loadFromFile(std::string loadPath){
    std::ifstream ifsLoadSequence(loadPath.c_str());
    int backboneIndex;
    int sequenceIndex;
    std::string cigarSequence;
    std::string sequence;
    if (ifsLoadSequence.is_open()){
        ifsLoadSequence >> backboneIndex >> sequenceIndex >> cigarSequence >> sequence;
        ifsLoadSequence.close();
    }
    else 
    {
        std::cout << "File not opened!!";
    }
     // create object and return it
    Sequence *seq = new Sequence(backboneIndex, sequenceIndex, cigarSequence, sequence);
    return seq;
}