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
    long long int start_index = 0;
    long long int node_length = 0;
    short int next_list_length = 0;

    std::vector<suffix_node *> next_list = {NULL, NULL, NULL, NULL, NULL, NULL};

    suffix_node(const long long int start = 0, 
                const long long int length = 0, 
                const short int node_list_length = 0, 
                const std::vector<suffix_node *> node_list = {NULL, NULL, NULL, NULL, NULL, NULL})
    {
        start_index = start;
        node_length = length;
        next_list_length = node_list_length;

        for(int i = 0; i < node_list.size(); i++)
        {
            next_list.push_back(node_list.at(i));
        }
    }

    void refresh_nodes()
    {
        std::vector<suffix_node *> refreshed_next_list(6, NULL);
        next_list = refreshed_next_list;
        next_list_length = 0;
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
    if(text_len == 0)
    {
        text = text + "$";
        text_len = text.length();
    }

    std::cout << "Text Length: " << text_len << "\tTotal Length:" << text.length() << std::endl;

    suffix_node* root = new suffix_node();

    long long int internal_nodes = 0;
    long long int outgoing_edges = 0;

    for(int i = 0; i < text_len; i++)
    {
        // std::cout << std::endl << "Started suffix: " << i << std::endl;
        suffix_node* current_node = root;
        int previous_length = root->node_length;

        std::cout << std::endl << "STARTED Adding: " << text.substr(i, text_len - i) << " to the Trie" << std::endl;
        for(int j = i; j < text_len; j++)
        {
            long long int node_length = current_node->node_length;

            std::cout   << "\tj : " << j << "\t"
                        << "i: "  << i << "\t"
                        << "s: "  << current_node->start_index << "\t"
                        << "length: "  << current_node->node_length << "\t"
                        << "String: " << text.substr(current_node->start_index, node_length) << " vs " << text.substr(j, text_len - j) << std::endl;

            std::cout << "Previous Length: " << previous_length << std::endl;
            int collateral = 0;
            if(previous_length == 1)
            {
                collateral = 1;
            }
            previous_length = current_node->node_length;

            if(((j - i) < node_length + collateral) && (node_length > 1))
            {
                if(text[j] == text[j - i + current_node->start_index + collateral])
                {
                    std::cout << "\t\tEqualling at j: " << j << "\tWith letter: " << text[j] << std::endl;
                    continue;
                }
                else
                {
                    long long int split_start  = j - i + current_node->start_index + collateral;
                    long long int split_length = current_node->node_length - j + i + collateral;

                    std::cout << "\t\tNOT equalling at j: " << j << "\tWith letter: " << text[j] << " != " << text[split_start] << std::endl;

                    std::cout << "\t\tNew split: " << text.substr(current_node->start_index, node_length - split_length) << " | " << text.substr(split_start, split_length) 
                    << "\ti: " << i << "\tj: " << j << "\tcurrent_start: " << current_node->start_index << std::endl;

                    suffix_node* split_node = new suffix_node(split_start, split_length, current_node->next_list_length, current_node->next_list);

                    current_node->refresh_nodes();

                    std::cout << "\t\tAdding split node: " << text.substr(split_start, split_length) << "\tStarting: " << text[split_start] << "\tStart: " << split_start << "\tLength: " << split_length << std::endl;
                    current_node->next_list[HASH(text[split_start])] = split_node;
                    current_node->next_list_length += 1;

                    internal_nodes += 1;
                    std::cout << "\t\t\tAdding Internal Node. Internal Nodes = " << internal_nodes << std::endl;

                    outgoing_edges += 1;
                    std::cout << "\t\t\tAdding Outgoing Edge. Outgoing Edges = " << outgoing_edges << std::endl;

                    current_node->node_length -= split_length;

                    std::cout << "->" << text.substr(split_start, split_length) << std::endl;
                }
            }
            else
            {
                std::cout << "\t\tCan't compare because of range. Current Node: " << text.substr(current_node->start_index, node_length) << std::endl;
            }

            if(current_node->next_list[HASH(text[j])] == NULL)
            {
                std::cout << "\t\tCreating new node at j: " << j << "\tWith letter: " << text[j] << "\tSubstring: " << text.substr(j, text_len - j) << std::endl;
                std::cout << "->" << text.substr(j, text_len - j) << std::endl;

                if(current_node->next_list_length == 0)
                {
                    internal_nodes += 1;
                    std::cout << "\t\t\tAdding Internal Node. Internal Nodes = " << internal_nodes << std::endl;
                }

                suffix_node* new_node = new suffix_node(j, text_len - j);
                current_node->next_list[HASH(text[j])] = new_node;

                current_node->next_list_length += 1;

                outgoing_edges += 1;
                std::cout << "\t\t\tAdding Outgoing Edge. Outgoing Edges = " << outgoing_edges << std::endl;

                current_node = current_node->next_list[HASH(text[j])];

                break;
            }
            else
            {
                std::cout << "\t\tTraveling to next node from j: " << j << "\twith letter: " << text[j] << "\tFrom Node: " << text.substr(current_node->start_index, current_node->node_length) << std::endl;
                current_node = current_node->next_list[HASH(text[j])];
            }

        }
        std::cout << "FINISHED Adding: " << text.substr(i, text_len - i) << " to the Trie" << std::endl;
        std::cout << "Internal Nodes: " << internal_nodes << std::endl;
        std::cout << "Outgoing Edges: " << outgoing_edges << std::endl;
        // std::cout << "Finished suffix: " << i << std::endl << std::endl;
    }

    std::cout << internal_nodes << std::endl;
    std::cout << outgoing_edges << std::endl;
}// create_suffix_tree

#endif // A2_HPP
