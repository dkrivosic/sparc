# include <string>

class Sequence
{
    private:
        int backboneIndex;
        int sequenceIndex;
        std::string sequence;
        Sequence();
    public:
        static Sequence createFromFile(std::string);
        ~Sequence();
};