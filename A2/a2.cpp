#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


#include "a2.hpp"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " text_file" << std::endl;
        return -1;
    }

    const char *text_file_path = argv[1];

    if (strlen(text_file_path) < 1) {
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

    // now running your awesome code from a2.hpp
    auto t0 = std::chrono::system_clock::now();

    create_suffix_tree(text);

    auto t1 = std::chrono::system_clock::now();

    auto elapsed_par = std::chrono::duration<double>(t1 - t0);

    std::cout << elapsed_par.count() << std::endl;

    return 0;
} // main