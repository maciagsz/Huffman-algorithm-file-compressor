#include "utils.h"

std::string getFileContent(const std::string filepath)
{
    std::fstream input_file(filepath, std::ios::in | std::ios::binary);
    if (input_file)
    {
        std::string input_content;
        input_file.seekg(0, std::ios::end);
        input_content.resize(input_file.tellg());
        input_file.seekg(0, std::ios::beg);
        input_file.read(&input_content[0], input_content.size());
        input_file.close();
        return input_content;
    }
    throw(errno);
}