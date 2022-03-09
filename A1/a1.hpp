/*  SHRIRAM
 *  RAVI
 *  shriramr
 */

#ifndef A1_HPP
#define A1_HPP

#define INITIAL_INDEX 32
#define FINAL_INDEX 126
#define ASCII_RANGE FINAL_INDEX - INITIAL_INDEX + 1
#define HASH(character) character - INITIAL_INDEX

unsigned short int calculate_sigma_len(const char* text, const char* pattern, 
                                        const unsigned long long int &text_len, const unsigned short int &pattern_len, 
                                        std::vector<long long int> &sigma)
{
    unsigned short int      sigma_len           = 0;

    for(unsigned short int i = 0; i < pattern_len; i++)
    {
        if(sigma[HASH(pattern[i])] == -1)
        {
            sigma_len += 1;
            sigma[HASH(pattern[i])] = 0;
        }
    }

    for(unsigned long long int i = 0; i < text_len; i++)
    {
        if(sigma[HASH(text[i])] == -1)
        {
            sigma_len += 1;
            sigma[HASH(text[i])] = 0;
        }
        sigma[HASH(text[i])] += 1;
    }

    return sigma_len;
}

void populate_occ_matrix(const char* pattern, const unsigned short int &pattern_len, std::vector<std::vector<short int>> &occ_matrix)
{
    for(unsigned short int i = 0; i < pattern_len; i++)
    {
        for(unsigned short int j = i + 1; j < pattern_len; j++)
        {
            occ_matrix[HASH(pattern[i])][j] = i;
        }
    }
}

void bad_character_exploit(const char *text, const char *pattern)
{
    const unsigned long long int    text_len            = strlen(text);
    const unsigned short int        pattern_len         = strlen(pattern);
    unsigned short int              sigma_len           = 0;
    unsigned long long int          one_shift           = 0;
    unsigned long long int          many_shift          = 0;
    unsigned long long int          comparisons         = 0;
    unsigned short int              frequent_mismatch   = 0;
    double                          probability         = 1.0;

    std::vector<long long int> sigma(ASCII_RANGE, -1);
    sigma_len += calculate_sigma_len(text, pattern, text_len, pattern_len, sigma);

    std::vector<std::vector<short int>> occ_matrix(ASCII_RANGE , std::vector<short int> (ASCII_RANGE, -1));
    populate_occ_matrix(pattern, pattern_len, occ_matrix);

    std::vector<unsigned long long int> pattern_mismatch(pattern_len);
    std::fill(pattern_mismatch.begin(), pattern_mismatch.end(), 0);

    for(int i = 0; i <= (text_len - pattern_len); )
    {
        int j = 0;
        unsigned short int shift = 1;

        for(j = pattern_len - 1; j >= 0; j--)
        {
            comparisons += 1;

            if(text[i + j] != pattern[j])
            {
                pattern_mismatch[j] += 1;

                if(occ_matrix[HASH(text[i + j])][j] != -1)
                    shift = std::max(1, j - occ_matrix[HASH(text[i + j])][j]);
                else
                    shift = j + 1;

                if(shift == 1)
                    one_shift += 1;
                else
                    many_shift += 1;

                i += shift;

                break;
            }
        }

        if(j < 0)
        {
            shift = 1;
            if(shift == 1)
                one_shift += 1;
            
            i += shift;
        }
    }

    unsigned short int max = 0;
    for(int i = 0; i < pattern_len; i++)
    {
        if(max <= pattern_mismatch[i])
        {
            max = pattern_mismatch[i];
            frequent_mismatch = i + 1;
        }
        probability *= double(sigma[HASH(pattern[i])]) / double(text_len);
    }

    std::cout << text_len           << std::endl;
    std::cout << pattern_len        << std::endl;
    std::cout << sigma_len          << std::endl;
    std::cout << one_shift          << std::endl;
    std::cout << many_shift         << std::endl;
    std::cout << comparisons        << std::endl;
    std::cout << frequent_mismatch  << std::endl;
    std::cout << std::fixed << std::setprecision(6) << probability << std::endl;

}// bad_character_exploit

#endif // A1_HPP
