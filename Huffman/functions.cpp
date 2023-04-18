#include <iostream>
#include <fstream>

#include "functions.h"
#include "utils.h"

void makeFrequencyDictionary(const std::string &text, std::map<char, int> &frequency)
{
    for (const char &character : text)
    {
        int counter = frequency.count(character);
        if (counter == 0)
            frequency[character] = 1;
        else
            frequency[character] += 1;
    }
}

void loadFrequencyDictionary(const std::string &dict_filepath, std::map<char, int> &frequency)
{
    std::ifstream freq_file(dict_filepath, std::ios::in | std::ios::binary);

    if (!freq_file.is_open())
    {
        std::cout << "Wystapil blad podczas otwierania pliku slownika" << std::endl;
        throw(errno);
    }

    frequency.clear();

    char character_buffer;
    while (freq_file.get(character_buffer))
    {
        int freq = 0;
        freq_file.read((char *)&freq, sizeof(int));

        frequency[character_buffer] = freq;
    }
    freq_file.close();
}

void saveFrequencyDictionary(const std::string &dict_filepath, const std::map<char, int> &frequency)
{
    std::ofstream freq_file(dict_filepath, std::ios::out | std::ios::trunc);

    if (!freq_file.is_open())
    {
        std::cout << "Wystapil blad podczas otwierania pliku slownika" << std::endl;
        throw(errno);
    }

    for (const auto &pair : frequency)
    {
        freq_file.write(&pair.first, sizeof(pair.first));
        freq_file.write((char *)&pair.second, sizeof(int));
    }
    freq_file.close();
}

void makeHeap(std::priority_queue<Node *, std::vector<Node *>, NodeComparator> &minBinaryHeap, const std::map<char, int> &frequency)
{
    while (!minBinaryHeap.empty())
        minBinaryHeap.pop();

    for (const auto &pair : frequency)
    {
        minBinaryHeap.push(new Node(pair.second, pair.first));
    }

    Node *top, *left, *right;

    while (minBinaryHeap.size() > 1)
    {
        left = minBinaryHeap.top();
        minBinaryHeap.pop();

        right = minBinaryHeap.top();
        minBinaryHeap.pop();

        top = new Node(left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        minBinaryHeap.push(top);
    }
}

void calculateCodes(Node *root, std::map<char, std::string> &dictionary, std::string code)
{
    if (root->left == NULL && root->right == NULL)
    {
        root->code = code;
        dictionary[root->character] = root->code;
    }
    else
    {
        calculateCodes(root->left, dictionary, code + "0");
        calculateCodes(root->right, dictionary, code + "1");
    }
}

void encode(const std::string &input_filepath, const std::string &output_filepath, std::map<char, std::string> &dictionary)
{
    std::ifstream input_file(input_filepath, std::ios::in);
    std::ofstream output_file(output_filepath, std::ios::out | std::ios::trunc);

    if (!input_file.is_open() && !output_file.is_open())
    {
        std::cout << "Wystapil blad podczas otwierania plikow" << std::endl;
        throw(errno);
    }

    char next_byte = 0;
    int bit_counter = 0;
    char character_buffer;

    while (input_file.get(character_buffer))
    {
        for (int i = 0; i < dictionary[character_buffer].size(); i++)
        {
            if (bit_counter == 8)
            {
                output_file.write(&next_byte, 1);
                next_byte = 0;
                bit_counter = 0;
            }

            if (dictionary[character_buffer][i] == '1')
                next_byte |= (0x01 << bit_counter);

            bit_counter++;
        }
    }

    if (bit_counter > 0)
    {
        output_file.write(&next_byte, 1);
    }
    output_file.close();
}

void compress(const std::string &input_filepath, const std::string &output_filepath, const std::string &dict_filepath)
{
    std::string input_content = getFileContent(input_filepath);
    std::map<char, int> frequency;
    std::map<char, std::string> dictionary;
    std::priority_queue<Node *, std::vector<Node *>, NodeComparator> minBinaryHeap;

    makeFrequencyDictionary(input_content, frequency);
    saveFrequencyDictionary(dict_filepath, frequency);
    makeHeap(minBinaryHeap, frequency);
    calculateCodes(minBinaryHeap.top(), dictionary);
    encode(input_filepath, output_filepath, dictionary);
}

void decompress(const std::string &input_filepath, const std::string &output_filepath, const std::string &dict_filepath)
{
    std::map<char, int> frequency;
    std::map<char, std::string> dictionary;
    std::priority_queue<Node *, std::vector<Node *>, NodeComparator> minBinaryHeap;

    loadFrequencyDictionary(dict_filepath, frequency);
    makeHeap(minBinaryHeap, frequency);
    calculateCodes(minBinaryHeap.top(), dictionary);
    decode(input_filepath, output_filepath, dictionary, frequency);
}

void decode(const std::string &input_filepath, const std::string &output_filepath, std::map<char, std::string> &dictionary, std::map<char, int> &frequency)
{
    std::ifstream input_file(input_filepath, std::ios::in | std::ios::binary);
    std::ofstream output_file(output_filepath, std::ios::out);

    if (!input_file.is_open() && !output_file.is_open())
    {
        std::cout << "Wystapil blad podczas otwierania plikow" << std::endl;
        return;
    }

    std::string code = "";
    char character_buffer;

    while (input_file.get(character_buffer))
    {
        for (int i = 0; i < 8; i++)
        {
            if ((character_buffer >> i) & 0x01)
                code += '1';
            else
                code += '0';

            for (auto iterator = dictionary.cbegin(); iterator != dictionary.cend();)
            {
                if (iterator->second == code)
                {
                    char character = iterator->first;
                    output_file.write(&character, 1);
                    code.clear();
                    frequency[iterator->first] -= 1;

                    if (frequency[iterator->first] == 0)
                    {
                        dictionary.erase(iterator++);
                        continue;
                    }
                }

                iterator++;
            }
        }
    }
}