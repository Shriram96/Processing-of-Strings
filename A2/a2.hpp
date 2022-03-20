/*  SHRIRAM
 *  RAVI
 *  shriramr
 */

#ifndef A2_HPP
#define A2_HPP

// #define INITIAL_INDEX 32
// #define FINAL_INDEX 126
// #define ASCII_RANGE FINAL_INDEX - INITIAL_INDEX + 1
// #define HASH(character) character - INITIAL_INDEX

struct suffix_node
{
    unsigned long long int start_index;
    unsigned long long int end_index;
    unsigned short int next_list_length;

    std::vector<suffix_node *> next_list;

    suffix_node(const unsigned long long int start = 0, 
                const unsigned long long int end = 0, 
                const unsigned short int node_list_length = 0, 
                const std::vector<suffix_node *> node_list = {NULL, NULL, NULL, NULL, NULL, NULL})
    {
        start_index = start;
        end_index = end;
        next_list_length = node_list_length;

        for(int i = 0; i < node_list.size(); i++)
        {
            next_list.push_back(node_list[i]);
        }
    }

    void refresh_nodes()
    {
        for(int i = 0; i < 6; i++)
        {
            if(next_list[i])
            {
                next_list[i] = NULL;
            }
        }
        next_list_length = 0;
    }

};

unsigned short int HASH(const char &letter)
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

void create_suffix_tree(const std::string &text)
{
    unsigned long long int text_len = text.size();

    suffix_node* head = new suffix_node();

    unsigned long long int internal_nodes = 0;
    unsigned long long int outgoing_edges = 0;

    for(int i = 0; i < text_len; i++)
    {
        // std::cout << std::endl << "Started suffix: " << i << std::endl;
        suffix_node* current_node = head;

        std::cout << std::endl << "STARTED Adding: " << text.substr(i, text_len - i + 1) << " to the Trie" << std::endl;
        for(int j = i; j < text_len; j++)
        {
            std::cout   << "\tj: " << j << "\t"
                        << "i:"  << i << "\t"
                        << "e:"  << current_node->end_index << "\t"
                        << "s:"  << current_node->start_index << std::endl;

            if((j - i) < (current_node->end_index - current_node->start_index))
            {
                if(text[j] == text[j - i + current_node->start_index])
                {
                    std::cout << "\t\tEqualling at j: " << j << "\tWith letter: " << text[j] << std::endl;
                    continue;
                }
                else
                {
                    unsigned long long int split_start  = j - i + current_node->start_index;
                    unsigned long long int split_end    = current_node->end_index;

                    std::cout << "\t\tNOT equalling at j: " << j << "\tWith letter: " << text[j] << std::endl;

                    std::cout << "\t\tNew split: " << text.substr(current_node->start_index, split_start - current_node->start_index) << " | " << text.substr(split_start, split_end - split_start + 1) 
                    << "\ti: " << i << "\tj: " << j << "\tcurrent_start: " << current_node->start_index << std::endl;

                    suffix_node* split_node = new suffix_node(split_start, split_end, current_node->next_list_length, current_node->next_list);
                    
                    current_node->refresh_nodes();

                    current_node->next_list[HASH(split_start)] = split_node;
                    current_node->next_list_length += 1;

                    internal_nodes += 1;
                    std::cout << "\t\t\tAdding Internal Node. Internal Nodes = " << internal_nodes << std::endl;

                    outgoing_edges += 1;
                    std::cout << "\t\t\tAdding Outgoing Edge. Outgoing Edges = " << outgoing_edges << std::endl;

                    current_node->end_index = split_start - 1;
                }
            }
            else
            {
                std::cout << "\t\tCan't compare because of range" << std::endl;
            }

            if(current_node->next_list[HASH(text[j])] == NULL)
            {
                std::cout << "\t\tCreating new node at j: " << j << "\tWith letter: " << text[j] << "\tSubstring: " << text.substr(j, text_len - j + 1) << std::endl;

                if(current_node->next_list_length == 0)
                {
                    internal_nodes += 1;
                    std::cout << "\t\t\tAdding Internal Node. Internal Nodes = " << internal_nodes << std::endl;
                }

                current_node->next_list[HASH(text[j])] = new suffix_node(j, text_len);
                current_node->next_list_length += 1;

                outgoing_edges += 1;
                std::cout << "\t\t\tAdding Outgoing Edge. Outgoing Edges = " << outgoing_edges << std::endl;

                current_node = current_node->next_list[HASH(text[j])];

                break;
            }
            else
            {
                std::cout << "\t\tTraveling to next node from j: " << j << "\twith letter: " << text[j] << std::endl;
                current_node = current_node->next_list[HASH(text[j])];
            }

        }
        std::cout << "FINISHED Adding: " << text.substr(i, text_len - i + 1) << " to the Trie" << std::endl;
        // std::cout << "Finished suffix: " << i << std::endl << std::endl;
    }

    std::cout << internal_nodes << std::endl;
    std::cout << outgoing_edges << std::endl;
}// create_suffix_tree

#endif // A2_HPP
