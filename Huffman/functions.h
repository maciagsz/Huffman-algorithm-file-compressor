#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <map>
#include <queue>
#include <vector>

#include "node.h"

/**
 *  Tworzy slownik unikatowych znakow na podstawie przeslanego
 *  tekstu oraz zlicza ich wystapienie.
 *
 *  @param text referencja do tekstu do wyszukania unikatowych znakow
 *  @param frequency referencja do frekwencji wystepowania znakow
 */
void makeFrequencyDictionary(const std::string &text, std::map<char, int> &frequency);

/**
 *  Laduje slownik unikatowych znakow z pliku,
 *  sciezka do pliku jest okreslona w zmiennej 'dict_filepath'
 *  klasy.
 *
 *  @param dict_filepath sciezka do pliku slownikowego
 *  @param frequency referencja do frekwencji wystepowania znakow
 */
void loadFrequencyDictionary(const std::string &dict_filepath, std::map<char, int> &frequency);

/**
 *  Zapisuje slownik unikatowych znakow do pliku,
 *  sciezka do pliku jest okreslona w zmiennej 'dict_filepath'
 *  klasy.
 *
 *  @param dict_filepath sciezka do pliku slownikowego
 *  @param frequency referencja do frekwencji wystepowania znakow
 */
void saveFrequencyDictionary(const std::string &dict_filepath, const std::map<char, int> &frequency);

/**
 *  Tworzy drzewo Huffmana w postaci kolejki priorytetowej
 *  <priority_queue> oraz zapelnia je danymi ze slownika.
 *
 *  @param minBinaryHeap referencja do kolejki priorytetowej
 *  @param frequency referencja do frekwencji wystepowania znakow
 */
void makeHeap(std::priority_queue<Node *, std::vector<Node *>, NodeComparator> &minBinaryHeap, const std::map<char, int> &frequency);

/**
 *  Oblicza kody dla kazdego unikatowego znaku przemieszczajac
 *  sie po drzewie Huffmana okreslonym w zmiennej 'minBinaryHeap'.
 *
 *  @param root wskaznik na koniec kolejki priorytetowej
 *  @param dictionary referencja do slownika
 *  @param code argument opcjonalny do wewnetrznego zastosowania
 */
void calculateCodes(Node *root, std::map<char, std::string> &dictionary, std::string code = "");

/**
 *  Koduje plik ze sciezki okreslonej w zmiennej klasowej
 *  'input_filepath' do sciezki wyjsciowej 'output_filepath',
 *  funkcja ta jedynie opakowuje funkcje do prostej
 *  uzywalnej formy.
 *
 *  @param intput_filepath sciezka do pliku wejsciowego
 *  @param output_filepath sciezka do pliku wyjsciowego
 *  @param dictionary referencja do slownika
 */
void encode(const std::string &input_filepath, const std::string &output_filepath, std::map<char, std::string> &dictionary);

/**
 *  Odkodowuje plik ze sciezki okreslonej w zmiennej klasowej
 *  'input_filepath' do sciezki wyjsciowej 'output_filepath'
 *  funkcja ta jedynie opakowuje funkcje prywatne do prostej
 *  uzywalnej formy.
 *
 *  @param intput_filepath sciezka do pliku wejsciowego
 *  @param output_filepath sciezka do pliku wyjsciowego
 *  @param dictionary referencja do slownika
 *  @param frequency referencja do frekwencji wystepowania znakow
 */
void decode(const std::string &input_filepath, const std::string &output_filepath, std::map<char, std::string> &dictionary, std::map<char, int> &frequency);

/**
 *  Interfejs sluzacy do kompresji pliku wejsciowego do wyjsciowego
 *  i zapisania pliku slownikowego za pomoca algorytmu Huffmana.
 *
 *  @param intput_filepath sciezka do pliku wejsciowego
 *  @param output_filepath sciezka do pliku wyjsciowego
 *  @param dict_filepath sciezka do pliku slownikowego
 *
 */
void compress(const std::string &input_filepath, const std::string &output_filepath, const std::string &dict_filepath);

/**
 *  Interfejs sluzacy do dekompresji pliku wejsciowego do wyjsciowego
 *  przy uzyciu okreslonego slownika.
 *
 *  @param intput_filepath sciezka do pliku wejsciowego
 *  @param output_filepath sciezka do pliku wyjsciowego
 *  @param dict_filepath sciezka do pliku slownikowego
 *
 */
void decompress(const std::string &input_filepath, const std::string &output_filepath, const std::string &dict_filepath);

#endif