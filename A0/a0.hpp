/*  SHRIRAM
 *  RAVI
 *  shriramr
 */

#ifndef A0_HPP
#define A0_HPP

#include <vector>
#include <cstring>
#include <limits>


long long int bitap_fuzzy_bitwise_search(const char *text, const char *pattern, unsigned int alpha)
{
    long long int result = -1;
    int m = strlen(pattern);
    unsigned long *R;
    unsigned long pattern_mask[CHAR_MAX+1];
    int i, d;

    if (pattern[0] == '\0') return result;
    if (m > 128) return result;

    /* Initialize the bit array R */
    R = static_cast<unsigned long*>(malloc((alpha+1) * sizeof *R));
    for (i=0; i <= alpha; ++i)
        R[i] = ~1;

    /* Initialize the pattern bitmasks */
    for (i=0; i <= CHAR_MAX; ++i)
        pattern_mask[i] = ~0;
    for (i=0; i < m; ++i)
        pattern_mask[pattern[i]] &= ~(1UL << i);

    for (i=0; text[i] != '\0'; ++i) {
        /* Update the bit arrays */
        unsigned long old_Rd1 = R[0];

        R[0] |= pattern_mask[text[i]];
        R[0] <<= 1;

        for (d=1; d <= alpha; ++d) {
            unsigned long tmp = R[d];
            /* Substitution is all we care about */
            R[d] = (old_Rd1 & (R[d] | pattern_mask[text[i]])) << 1;
            old_Rd1 = tmp;
        }

        if (0 == (R[alpha] & (1UL << m))) {
            result = (i - m) + 2;
            break;
        }
    }

    free(R);
    return result;
}// bitap_fuzzy_bitwise_search

long long int first_match_search(const char *text, const char *pattern, unsigned int alpha)
{
    long long int result = -1;
    unsigned long long int text_len = strlen(text);
    unsigned short int pattern_len = strlen(pattern);

    for(unsigned long long int i = 0; i <= text_len - pattern_len; i++)
    {
        short int step_alpha = alpha;
        for(unsigned short int j = 0; j < pattern_len; j++)
        {
            if(text[i + j] != pattern[j])
            {
                step_alpha -= 1;
            }
            if(step_alpha < 0)
            {
                break;
            }   
        }
        if(step_alpha >= 0)
        {
            result = i + 1;
            break;
        }
    }

    return result;
}// first_match_search

#endif // A0_HPP