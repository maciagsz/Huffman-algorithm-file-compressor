#include "node.h"

Node::Node(int frequency, char character) : frequency(frequency),
                                            character(character)
{
}

Node::Node(int frequency) : frequency(frequency)
{
}

bool NodeComparator::operator()(const Node *leftNode, const Node *rightNode)
{
    return leftNode->frequency > rightNode->frequency;
}