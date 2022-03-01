#!/Users/shriramr/opt/anaconda3/bin/python
# SHRIRAM
# RAVI
# shriramr
import re
import sys
import time
import regex

class Comparator:
    text: str = ""
    pattern: str = ""
    def __init__(self, in_text_file_path: str, in_pattern: str) -> None:
        self.text = self.get_text_from_file(in_text_file_path)
        self.pattern = in_pattern
        return

    def get_text_from_file(self, text_file_path: str) -> str:
        text_file = open(text_file_path, "r")  
        text = text_file.read()
        text_file.close()
        return text

    def get_first_match(self, alpha: int) -> int:
        text_len = len(self.text)
        pattern_len = len(self.pattern)
        target = pattern_len - alpha
        for i in range(text_len - pattern_len + 1):
            count = 0
            for j in range(pattern_len):
                if self.text[i + j] == self.pattern[j]:
                    count += 1
                if count >= target:
                    return i + 1
        return -1

    def get_all_matches(self, alpha: int) -> int:
        text_len = len(self.text)
        pattern_len = len(self.pattern)
        target = pattern_len - alpha
        total = 0
        for i in range(text_len - pattern_len + 1):
            count = 0
            for j in range(pattern_len):
                if self.text[i + j] == self.pattern[j]:
                    count += 1
                if count >= target:
                    total += 1
                    break
        return total

    def fuzzy_first_match(self, alpha: int) -> int:
        text_len = len(self.text)
        pattern_len = len(self.pattern)

        bit_map = [~1] * (alpha + 1)
        pattern_mask = [~0] * 128

        for i in range(pattern_len):
            pattern_mask[ord(self.pattern[i])] &= ~(1 << i)

        for i in range(text_len):
            old_first_bit = bit_map[0]

            bit_map[0] |= pattern_mask[ord(self.text[i])]
            bit_map[0] <<= 1

            for j in range(1, alpha + 1):
                tmp = bit_map[j]
                bit_map[j] = (old_first_bit & (bit_map[j] | pattern_mask[ord(self.text[j])])) << 1
                old_first_bit = tmp
            
            if (bit_map[alpha] & 1 << pattern_len) == 0:
                # print(self.text[i - pattern_len + 1])
                return i - pattern_len + 2


        # print(bit_map)
        # print(pattern_mask)
        return -1
    
    def regex_first_match(self, alpha) -> int:
        
        # match = regex.match('(%s){e<=1}' %self.text, '%s' %self.pattern)
        match = regex.match('(%s){e<=1}'%self.text, '%s'%self.pattern)
        print(match)


if __name__ == "__main__":
    start = time.time()
    text_file_path = str(sys.argv[1])
    pattern = str(sys.argv[2])
    alpha = int(sys.argv[3])
    comparator = Comparator(text_file_path, pattern)
    # position = 0
    # position = comparator.get_first_match(alpha)
    # position_2 = 0
    # position_2 = comparator.fuzzy_first_match(alpha)
    # print(position)
    # print(position_2)
    # comparator.regex_first_match(alpha)
    all_matches = comparator.get_all_matches(alpha)
    print(all_matches)
    end = time.time()
    print("Dale: ", end - start)