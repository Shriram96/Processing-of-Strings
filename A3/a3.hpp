/*  SHRIRAM
 *  RAVI
 *  shriramr
 */

#ifndef A3_HPP
#define A3_HPP

int get_LCP(const std::string &text, const size_t &text_len, const int &first, const int &second)
{
    int LCP = 0;
    for(int i = 0; i < text_len; i++)
    {
        if(text[first + i] == text[second + i] && (text[first + i] != '$' && text[second + i] != '$'))
        {
            LCP += 1;
        }
        else
        {
            break;
        }
    }
    return LCP;
}

std::vector<int> get_LCP_Array(const std::string &text, const std::vector<int> &GSA)
{
    size_t GSA_size = GSA.size();
    size_t text_len = text.length();

    std::vector<int> LCP(GSA_size, 0);
    for(int i = 0; i < GSA_size; i++)
    {        
        LCP[i + 1] = get_LCP(text, text_len, GSA[i], GSA[i + 1]);
    }

    return LCP;
}// get_LCP_Array

#endif // A3_HPP
