//TODO: remove
#include <sstream>

#include <vector>

#include "../include/trie_iterator_printer.h"

std::map<std::string, int> tuple_counts;

void PrintTuple(std::vector<int>& current_tuple, std::ostream& out, char separator)
{
    std::ostringstream stream;

    for (std::vector<int>::iterator it = current_tuple.begin(); it != current_tuple.end(); ++it)
    {
        //out << *it << separator;
        stream << *it << separator;
    }
    //out << std::endl;
    //stream << std::endl;

    std::string tuple_string = stream.str();
    tuple_counts[tuple_string]++;
}


void PrintNode(ITrieIterator& trie_iterator, int printing_depth, std::ostream& out, int current_depth, std::vector<int>& current_tuple)
{
    if (trie_iterator.Open() == kFail)
    {
        if (current_depth == printing_depth)
        {
            PrintTuple(current_tuple, out, ',');
        }

        return;
    }

    int current_node_key;
    do
    {
        trie_iterator.Key(&current_node_key);
        current_tuple.push_back(current_node_key);

        PrintNode(trie_iterator, printing_depth, out, current_depth + 1, current_tuple);

        current_tuple.pop_back();
    }
    while (trie_iterator.Next() == kOK);

    trie_iterator.Up();
}


void TrieIteratorPrinter::Print(ITrieIterator& trie_iterator, int printing_depth, std::ostream& out)
{
    // Print the trie contents in-order
    std::vector<int> current_tuple;
    PrintNode(trie_iterator, printing_depth, out, 0, current_tuple);

    for (std::map<std::string, int>::iterator it = tuple_counts.begin(); it != tuple_counts.end(); ++it)
    {
        out << it->first << "[" << it->second << "]" << std::endl;
    }
}
