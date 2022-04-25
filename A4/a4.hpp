/*  SHRIRAM
 *  RAVI
 *  shriramr
 */

#ifndef A4_HPP
#define A4_HPP

#define SIGMA_LEN 6

// Took few inspirations from Professor Ben Langmead's (Johns Hopkins University) lecture on BWT and FM-Index

short int HASH(const char &letter)
{
    switch(letter)
    {
        case '$': return 0;
        case 'A': return 1;
        case 'C': return 2;
        case 'G': return 3;
        case 'N': return 4;
        case 'T': return 5;

        default:
            return 0;
    }
}

int get_occ_value(std::string &bwt_string, int &spacing_factor, std::vector<std::vector<int>> &occ_matrix, int index, char target_char)
{
    int bwt_string_length = bwt_string.length();

    int last_available_index = (index / spacing_factor);

    int return_val = occ_matrix[HASH(target_char)][last_available_index];

    for(int i = (last_available_index * spacing_factor) + 1; i <= index; i++)
    {
        if(bwt_string[i] == target_char)
        {
            return_val += 1;
        }
    }
    // std::cout << "Target: " << target_char << "\tfrom_index: " << last_available_index << "\ttill_index: " << index << "\t= " << return_val << std::endl;
    return return_val;
}

void fm_index(std::string &bwt_string, std::vector<int> &f_column, int &spacing_factor, std::vector<std::vector<int>> &occ_matrix, const std::string &pattern)
{
    long long int bwt_length = bwt_string.length();
    long long int pattern_length = pattern.length();
    long long int dollar_index = bwt_string.find("$");

    std::string text = "";

    long long int last_index = dollar_index;

    for(int i = 0; i < bwt_length; i++)
	{
		text = bwt_string[last_index] + text;
        int occ_value = get_occ_value(bwt_string, spacing_factor, occ_matrix, last_index, bwt_string[last_index]);
		last_index = f_column[HASH(bwt_string[last_index])] + occ_value - 1;
	}

    std::cout << text << std::endl;

    size_t start = 0;
    size_t end = bwt_length - 1;
    for(int i = pattern_length - 1; i >= 0; i--)
    {
        int start_occ_value = get_occ_value(bwt_string, spacing_factor, occ_matrix, start - 1, pattern[i]);
        int end_occ_value = get_occ_value(bwt_string, spacing_factor, occ_matrix, end, pattern[i]);
        start = f_column[HASH(pattern[i])] + (start ? start_occ_value : 0);
        // std::cout << "Start: " << f_column[HASH(pattern[i])] << " + " << (start ? start_occ_value : 0) << " = " << start << std::endl;
        end = f_column[HASH(pattern[i])] + end_occ_value - 1;
        // std::cout << "End: " << f_column[HASH(pattern[i])] << " + " << end_occ_value - 1 << " = " << end << std::endl;
        std::cout << ((start <= end) ? (end - start + 1) : 0) << std::endl;
    }
    
}// fm_index

#endif // A4_HPP
