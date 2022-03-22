/*  SHRIRAM
 *  RAVI
 *  shriramr
 */

#ifndef A2_HPP
#define A2_HPP

#define SIGMA_LENGTH 6
// #define INITIAL_INDEX 32
// #define FINAL_INDEX 126
// #define ASCII_RANGE FINAL_INDEX - INITIAL_INDEX + 1
// #define HASH(character) character - INITIAL_INDEX

struct suffix_node
{
    std::string node_string = "";

    short int next_list_length = 0;

    long long int node_string_length = 0;

    std::vector<suffix_node *> next_list = {NULL, NULL, NULL, NULL, NULL, NULL};

    suffix_node(const std::string string = "")
    {
        node_string = string;
        node_string_length = node_string.length();
    }

};

short int HASH(const char &letter)
{
    switch(letter)
    {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        case 'N': return 4;
        case '$': return 5;

        default:
            return 0;
    }
}

void create_suffix_tree(std::string &text)
{
    
    long long int text_len = text.find("$") + 1;
    text = text.substr(0, text_len);

    // std::cout << "Text Length: " << text_len << std::endl;

    suffix_node* root = new suffix_node("");
    root->next_list[HASH(text[0])] = new suffix_node(text);
    root->next_list_length += 1;

    long long int internal_nodes = 1;
    long long int outgoing_edges = 1;

    for(int i = 1; i < text_len; i++)
    {
        // std::cout << std::endl << "Started suffix: " << i << std::endl;
        suffix_node* current_node = root;

        // std::cout << std::endl << "STARTED Adding: " << text.substr(i, text_len - i) << " to the Trie" << std::endl;
        long long int j = i;
        while(j < text_len)
        {
            if(current_node->next_list[HASH(text[j])] != NULL)
            {
                suffix_node* child_node = current_node->next_list[HASH(text[j])];
                std::string node_string = child_node->node_string;
                long long int node_string_length = child_node->node_string_length;

                long long int k = j + 1;

                while(k - j < node_string_length && text[k] == node_string[k-j])
                {
                    k += 1;
                }

                if(k - j == node_string_length)
                {
                    current_node = child_node;
                    j = k;
                }
                else
                {
                    suffix_node* split_node = new suffix_node(node_string.substr(0, k - j));
                    split_node->next_list[HASH(text[k])] = new suffix_node(text.substr(k, text_len - k));
                    split_node->next_list[HASH(node_string[k - j])] = child_node;
                    split_node->next_list_length += 2;

                    child_node->node_string = node_string.substr(k - j);
                    child_node->node_string_length = child_node->node_string.length();
                    current_node->next_list[HASH(text[j])] = split_node;
                    split_node->next_list_length += 1;

                    internal_nodes += 1;
                    outgoing_edges += 2;
                }
            }
            else
            {
                if(current_node->next_list_length == 0)
                {
                    internal_nodes += 1;
                }
                current_node->next_list[HASH(text[j])] = new suffix_node(text.substr(j));
                current_node->next_list_length += 1;
                outgoing_edges += 1;
            }
            // std::cout << "FINISHED Adding: " << text.substr(i, text_len - i) << " to the Trie" << std::endl;
            // std::cout << "Internal Nodes: " << internal_nodes << std::endl;
            // std::cout << "Outgoing Edges: " << outgoing_edges << std::endl;
        }
    }

    std::cout << internal_nodes << std::endl;
    std::cout << outgoing_edges << std::endl;
}// create_suffix_tree

#endif // A2_HPP
