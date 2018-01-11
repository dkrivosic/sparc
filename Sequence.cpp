#include "Sequence.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <typeinfo>

Sequence::Sequence(int bIndex, int seqIndex, std::string cigar_seq, std::string seq) {
    backboneIndex = bIndex;
    sequenceIndex = seqIndex;
    cigar_sequence = cigar_seq;
    sequence = seq;
}

void Sequence::extractSequences(std::string pathToAlignments) {

    std::string saveDirectory = "sparc/sequence_alignments";

    const int dir_err = system("mkdir -p sparc/sequence_alignments");
    if (-1 == dir_err)
    {
        printf("Error creating directory!n");
        exit(1);
    }
    
    std::cout << "Saving reads to folder: '" + saveDirectory + "'"<< std::endl;

    // open alignments SAM file created GraphMap with CIGAR syntax
    std::string line;
    std::ifstream alignmentsFile(pathToAlignments);

    if (alignmentsFile.is_open()){
        std::istringstream iss;
        std::stringstream ss;
        int a;
        std::string b;
        int backboneIndexInt;
        int sequenceIndexInt;
        std::string cigarSequence;
        std::string sequence;

        for(int i = 0; i < 3; i++){
            getline(alignmentsFile, line);
        }

        while(getline(alignmentsFile, line)){
            // getline(alignmentsFile, line);
            iss.str(line);
            std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>());

            sequenceIndexInt = stoi(results[0]);
            backboneIndexInt = stoi(results[3]);
            cigarSequence = results[5];
            sequence = results[9];
            Sequence::saveToFile(saveDirectory, sequenceIndexInt, backboneIndexInt,cigarSequence, sequence);
            iss.clear();
        }
    } else {
        std::cout << "File is not opened. Exiting...";
        exit(1);
    }
    
    // close alignments file
    alignmentsFile.close();
}

void Sequence::saveToFile(std::string saveLocation, int sequenceIndexInt, int backboneIndexInt,std::string cigarSequence, std::string sequence){
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