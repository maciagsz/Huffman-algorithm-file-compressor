#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>

/**
 *  Funkcja wczytuje zawartosc pliku okreslonego w sciezce.
 *
 *  @param filepath sciezka do pliku
 *  @return funkcja zwraca std::string zawartosci
 */
std::string getFileContent(const std::string filepath);

#endif