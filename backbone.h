#include <string>

class Backbone
{
    private:
        Backbone(std::string);
    public:
        ~Backbone();
        static Backbone createFromFile(std::string);
};