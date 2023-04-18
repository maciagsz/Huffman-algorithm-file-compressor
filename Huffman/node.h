#ifndef NODE_H
#define NODE_H

#include <iostream>

/**
 *  Struktura ta to wezel przechowujacy informacje
 *  o czestotliwosci okreslonego znaku oraz jego kodu,
 *  stanowi element drzewa Huffmana.
 */
struct Node
{
public:
    int frequency;
    char character;
    std::string code;

    Node *left = NULL;
    Node *right = NULL;

    /**
     *  Domyslny konstruktor wezla pustego.
     *
     *  @param frequency czestotliwosc wystepowania znakow
     */
    Node(int frequency);

    /**
     *  Domyslny konstruktor wezla ze znakiem.
     *
     *  @param frequency czestotliwosc wystepowania znaku
     *  @param character znak dla jakiego jest przypisana czestotliwosc
     */
    Node(int frequency, char character);
};

/**
 *  Struktura ta sluzy jedynie do porownywania ze soba
 *  dwoch wezlow struktury 'Node', jej implementacja
 *  jest wymagana przez std::priority_queue.
 */
struct NodeComparator
{
public:
    bool operator()(const Node *leftNode, const Node *rightNode);
};

#endif