#include "kmer.h"
#include <string>

class KmerNode
{
    public:
        Kmer kmer;
        std::string link;
        int weight;
};