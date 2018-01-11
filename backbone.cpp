#include "backbone.h"
#include <fstream>
#include<iostream>

Backbone* Backbone::createFromFile(std::string filename)
{
    std::ifstream inFile;
    inFile.open(filename);
    if (!inFile) {
        std::cout << "Unable to open file datafile.txt"<<std::endl;
        exit(1);
    }
    std::string temp;
    inFile >> temp;
    std::string backbone;
    while (inFile >> temp) {
        backbone = backbone+temp;
    }
    inFile.close();
    return new Backbone(backbone);
}

Backbone::Backbone(std::string value)
{
    std::cout<<value;

}


Backbone::~Backbone()
{

}
