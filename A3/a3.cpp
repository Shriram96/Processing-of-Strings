#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>


#include "a3.hpp"

// Referred from: https://www.youtube.com/watch?v=a4mS6aKgxys
std::vector<int> readBinaryFile(std::string fileName, size_t size)
{
    int inputArray[size];

    std::ifstream inputFile;
    inputFile.open(fileName);
    if(inputFile)
    {
        inputFile.read(reinterpret_cast<char *>(inputArray), sizeof(int) * size);
        inputFile.close();
    }
    std::vector<int> GSA(inputArray, inputArray + size);
    return GSA;
}

// Referred from: https://www.youtube.com/watch?v=a4mS6aKgxys
void writeBinaryFile(std::vector<int> outputVector, std::string fileName)
{
    std::ofstream outputFile;
    int *outputArray = outputVector.data();
    outputFile.open(fileName);
    if(outputFile)
    {
        outputFile.write(reinterpret_cast<char *>(outputArray), sizeof(int) * outputVector.size());
        outputFile.close();
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "usage: " << argv[0] << " Test_Path GSA_Path Output_Path" << std::endl;
        return -1;
    }

    const char *text_file_path = argv[1];
    const char *gsa_file_path = argv[2];
    const char *output_file_path = argv[3];

    std::ifstream text_file(text_file_path);
    std::string text = "";
    if(text_file)
    {
        std::stringstream buffer;
        buffer << text_file.rdbuf();
        text = buffer.str();
    }

    int last_dollar = text.find_last_of('$') + 1;
    size_t size = last_dollar - std::count(text.begin(), text.end(), '$') + 1;
    std::vector<int> GSA;

    GSA = readBinaryFile(gsa_file_path, size);

    // now running your awesome code from a3.hpp
    std::vector<int> LCP = get_LCP_Array(text, GSA);

    writeBinaryFile(LCP, output_file_path);

    return 0;
} // main
