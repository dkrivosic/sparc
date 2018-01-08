# include <string>

class Sequence
{
    private:
        int backboneIndex;
        int sequenceIndex;
        std::string cigar_sequence;
        std::string sequence;
        Sequence();
    public:
        Sequence(int, int, std::string, std::string);
        static Sequence createFromFile();
 
        int getBackboneIndex()          {return backboneIndex;}
        int getSequenceIndex()          {return sequenceIndex;}
        std::string getCigarSequence()  {return cigar_sequence;}
        std::string getSequence()       {return sequence;}
 
        static void saveToFile(std::string, int, int, std::string, std::string);
        static Sequence loadFromFile(std::string, std::string);
       
        ~Sequence();
};