#pragma once
#include <string>

class Sequence
{
    private:
        int backboneIndex;
        int sequenceIndex;
        std::string cigar_sequence;
        std::string sequence;
        Sequence(int, int, std::string, std::string);

    public:
        static void extractSequences(std::string);
 
        int getBackboneIndex()          {return backboneIndex;}
        int getSequenceIndex()          {return sequenceIndex;}
        std::string getCigarSequence()  {return cigar_sequence;}
        std::string getSequence()       {return sequence;}
 
        static void saveToFile(std::string, int, int, std::string, std::string);
        static Sequence* loadFromFile(std::string);
       
        ~Sequence();
};