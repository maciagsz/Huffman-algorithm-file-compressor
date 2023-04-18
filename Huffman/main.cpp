#include <iostream>
#include <unistd.h>

#include "utils.h"
#include "functions.h"

void printHelp()
{
    std::cout << "Przyklad uzycia Huffman:" << std::endl
              << std::endl
              << "./Huffman -i 'plik_do_kompresji.txt' -o 'plik_skompresowany.bin' -s 'slownik.huf' -t k" << std::endl
              << std::endl
              << "\t-i [sciezka] : plik do przeprowadzenia operacji" << std::endl
              << "\t-o [sciezka] : plik wyjsciowy" << std::endl
              << "\t-s [sciezka] : plik slownikowy" << std::endl
              << "\t-t [k|d]     : tryb kompresji, dekompresji" << std::endl;
}

int main(int argc, char *argv[])
{
    std::string input_filepath = "", output_filepath = "", dict_filepath = "";
    bool mode = 0;
    while (true)
    {
        switch (getopt(argc, argv, "i:o:t:s:"))
        {
        case 'i':
            input_filepath = optarg;
            std::cout << "Plik wejsciowy: " << optarg << std::endl;
            continue;

        case 'o':
            output_filepath = optarg;
            std::cout << "Plik wyjsciowy: " << optarg << std::endl;
            continue;

        case 't':
            if (*optarg == 'k')
            {
                mode = 0;
                std::cout << "Tryb: "
                          << "kompresja" << std::endl;
            }
            else if (*optarg == 'd')
            {
                mode = 1;
                std::cout << "Tryb: "
                          << "dekompresja" << std::endl;
            }
            continue;

        case 's':
            dict_filepath = optarg;
            std::cout << "Plik slownikowy: " << optarg << std::endl;
            continue;

        case '?':
        case 'h':
        default:
            printHelp();
            break;

        case -1:
            break;
        }

        break;
    }

    if (!(input_filepath.empty() || output_filepath.empty() || dict_filepath.empty()))
    {
        if (mode == 0)
            compress(input_filepath, output_filepath, dict_filepath);
        if (mode == 1)
            decompress(input_filepath, output_filepath, dict_filepath);
    }
    else
    {
        printHelp();
    }

    return 0;
}