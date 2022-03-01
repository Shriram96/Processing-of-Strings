#include <algorithm>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>


#include "a0.hpp"


int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "usage: " << argv[0] << " text_file pattern alpha" << std::endl;
        return -1;
    }

    const char *text_file_path = argv[1];
    const char *pattern = argv[2];
    const unsigned int alpha = std::atoi(argv[3]);

    if (alpha < 1) {
        std::cout << "hey, alpha is too small even for debugging!" << std::endl;
        return -1;
    }

    std::ifstream text_file(text_file_path);
    std::string text = "";
    if(text_file)
    {
        std::stringstream buffer;
        buffer << text_file.rdbuf();
        text = buffer.str();
    }

    // now running your awesome code from a0.hpp
    auto t0 = std::chrono::system_clock::now();

    long long int result = bitap_fuzzy_bitwise_search(text.c_str(), pattern, alpha);
    // long long int result = first_match_search(text.c_str(), pattern, alpha);


    auto t1 = std::chrono::system_clock::now();

    auto elapsed_par = std::chrono::duration<double>(t1 - t0);
    std::cout << result << std::endl << elapsed_par.count() << std::endl;

    return 0;
} // main