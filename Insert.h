#pragma once
#include "Node.h"


class Insert
{
    public:
        Insert(Node*, Node*, std::string, std::string, int);
        Node *startNode;
        Node *endNode;
        std::string graphString;
        std::string insertString;
        int index;
};