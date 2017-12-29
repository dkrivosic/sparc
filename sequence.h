# include <string>

class Sequence
{
    private:
        int backboneIndex;
        int sequenceIndex;
        std::string sequence;
        Sequence();
    public:
        Sequence(int, int, std::string);
        static Sequence createFromFile();
 
        int getBackboneIndex()      {return backboneIndex;}
        int getsequenceIndex()      {return sequenceIndex;}
        std::string getSequence()   {return sequence;}
 
        void saveToFile(std::string);
        Sequence loadFromFile(std::string, std::string);
       
        ~Sequence();
};