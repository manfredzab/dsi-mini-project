// TODO: remove
#include <iostream>

#define PRINT_COUNTS 1

#if PRINT_COUNTS
#include <sstream>
#include <algorithm>
#endif

#include <vector>

#include "../include/trie_iterator_printer.h"

std::map<std::string, int> tuple_counts;
std::vector<std::string> sorted_tuples;

void PrintTuple(std::vector<int>& current_tuple, std::ostream& out, char separator)
{
#if PRINT_COUNTS
    std::ostringstream stream;
#endif

    for (std::vector<int>::iterator it = current_tuple.begin(); it != current_tuple.end(); ++it)
    {

#if PRINT_COUNTS
        stream << *it << separator;
#else
        out << *it << separator;
#endif
    }
#if PRINT_COUNTS
    std::string tuple_string = stream.str();
    //tuple_counts[tuple_string]++;
    sorted_tuples.push_back(tuple_string);
#else
    out << std::endl;
#endif
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

//        if ((current_node_key == 33) && (current_depth == 7))
//        if ((current_node_key == 100) && (current_depth == 3))
//        {
//            std::cout << "FUCK" << std::endl;
//        }
//        std::cout <<  current_node_key << "\t@\t" << current_depth << std::endl;

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
#if PRINT_COUNTS
//    for (std::map<std::string, int>::iterator it = tuple_counts.begin(); it != tuple_counts.end(); ++it)
//    {
//        out << it->first << "[" << it->second << "]" << std::endl;
//    }

    sort(sorted_tuples.begin(), sorted_tuples.end());
    for (std::vector<std::string>::iterator it = sorted_tuples.begin(); it != sorted_tuples.end(); ++it)
    {
        out << *it << std::endl;
    }
#endif
}
//
//void TrieIteratorPrinter::Print(ITrieIterator& trie_iterator, int printing_depth, std::ostream& out)
//{
//    // Print the trie contents in-order
//    std::vector<int>
//}

