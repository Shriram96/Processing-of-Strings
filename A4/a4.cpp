#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


#include "a4.hpp"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "usage: " << argv[0] << " bwt_file pattern" << std::endl;
        return -1;
    }

    const std::string pattern = argv[2];

    if (pattern.length() < 1) {
        std::cout << "hey, pattern is too small even for debugging!" << std::endl;
        return -1;
    }

    const char *text_file_path = argv[1];

    if (strlen(text_file_path) < 1) {
        std::cout << "hey, bwt_file is too small even for debugging!" << std::endl;
        return -1;
    }

    FILE* fp = fopen(text_file_path, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    char* line = NULL;
    size_t len = 0;
    
    // Get BWT_String
    std::string bwt_string;
    if ((getline(&line, &len, fp)) != -1) 
    {
        bwt_string = line;
        bwt_string.pop_back();
    }

    // Get Column F of LF-mapping
    std::vector<int> f_column(SIGMA_LEN);
    for (int i = 0; i < SIGMA_LEN; i++)
    {
        int result = fscanf(fp, "%d", &f_column[i]);
    }

    // Get Spacing factor used to compact OCC Matrix
    int spacing_factor;
    int result = fscanf(fp, "%d", &spacing_factor);

    // Get compacted OCC Matrix
    size_t bwt_string_length = bwt_string.length();
    int occ_column_size = (bwt_string_length / spacing_factor) + ((bwt_string_length % spacing_factor != 0) ? 1 : 0);

    std::vector<std::vector<int>> occ_matrix(SIGMA_LEN, std::vector<int> (occ_column_size));
    for (int i = 0; i < SIGMA_LEN; i++)
    {
        for(int j = 0; j < occ_column_size; j++)
        {
            int result = fscanf(fp, "%d", &occ_matrix[i][j]);
        }
    }

    fclose(fp);
    if (line)
        free(line);

    // now running your awesome code from a4.hpp
    auto t0 = std::chrono::system_clock::now();

    fm_index(bwt_string, f_column, spacing_factor, occ_matrix, pattern);

    auto t1 = std::chrono::system_clock::now();

    auto elapsed_par = std::chrono::duration<double>(t1 - t0);

    std::cout << elapsed_par.count() << std::endl;

    return 0;
} // main