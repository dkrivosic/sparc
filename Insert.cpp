#include "Insert.h"

Insert::Insert(Node *startNode, Node *endNode, std::string graphString, std::string insertString, int index) :
    startNode(startNode),
    endNode(endNode),
    graphString(graphString),
    insertString(insertString),
    index(index)
    {
    }