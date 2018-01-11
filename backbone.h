#pragma once
#include <string>

class Backbone
{
    private:
        Backbone(std::string);
    public:
        ~Backbone();
        std::string value;
        static Backbone* createFromFile(std::string);
};