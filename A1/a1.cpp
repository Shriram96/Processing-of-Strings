#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


#include "a1.hpp"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "usage: " << argv[0] << " text_file pattern" << std::endl;
        return -1;
    }

    const char *pattern = argv[1];
    const char *text_file_path = argv[2];

    if (strlen(pattern) < 1) {
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

    // now running your awesome code from a1.hpp
    auto t0 = std::chrono::system_clock::now();

    bad_character_exploit(text.c_str(), pattern);


    auto t1 = std::chrono::system_clock::now();

    auto elapsed_par = std::chrono::duration<double>(t1 - t0);

    std::cout << /*result << std::endl <<*/ elapsed_par.count() << std::endl;

    return 0;
} // main