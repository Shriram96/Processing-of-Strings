/*  SHRIRAM
 *  RAVI
 *  shriramr
 */

#ifndef A4_HPP
#define A4_HPP

#define SIGMA_LEN 6

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
    // std::cout << "BWT String: " << bwt_string << "\tLength: " << bwt_length << std::endl;
    long long int dollar_index = bwt_string.find("$");

    std::string text = "";

    // std::cout << "OCC Matrix: " << std::endl;
    // for(std::vector<int> a: occ_matrix)
    // {
    //     for(int i = 0; i < a.size(); i++)
    //     {
    //         std::cout << a[i] << "\t";
    //     }
    //     std::cout << std::endl;
    // }

    long long int last_index = dollar_index;

    for(int i = 0; i < bwt_length; i++)
	{
		text += bwt_string[last_index];
        int occ_index = get_occ_value(bwt_string, spacing_factor, occ_matrix, last_index, bwt_string[last_index]);
		last_index = f_column[HASH(bwt_string[last_index])] + occ_index - 1;
	}

    reverse(text.begin(), text.end());
    std::cout << text << std::endl;

    for(int i = pattern_length - 1; i >= 0; i--)
    {
        const char* P = &pattern[i];

        size_t a = 0;
        size_t b = bwt_length - 1;
    
        for(int j = pattern_length - i - 1; j >= 0 && a <= b; j--)
        {            
            int a_occ_index = get_occ_value(bwt_string, spacing_factor, occ_matrix, a - 1, P[j]);
            int b_occ_index = get_occ_value(bwt_string, spacing_factor, occ_matrix, b, P[j]);
            a = f_column[HASH(P[j])] + (a ? a_occ_index : 0);
            b = f_column[HASH(P[j])] + b_occ_index - 1;
        }
    
        std::cout << ((a <= b) ? (b - a + 1) : 0) << std::endl;
    }
    
}// fm_index

#endif // A4_HPP
