#define PRINT_COUNTS 1

#if PRINT_COUNTS
#include <sstream>
#include <algorithm>
#endif

#include <vector>

#include "../include/trie_iterator_printer.h"

namespace uk_ac_ox_cs_c875114
{

using std::string;
using std::vector;
using std::map;
using std::ostream;
using std::ostringstream;

map<string, int> tuple_counts;
vector<string> sorted_tuples;

void PrintTuple(vector<int>& current_tuple, ostream& out, char separator)
{
#if PRINT_COUNTS
    ostringstream stream;
#endif

    for (vector<int>::iterator it = current_tuple.begin(); it != current_tuple.end(); ++it)
    {

#if PRINT_COUNTS
        stream << *it << separator;
#else
        out << *it << separator;
#endif
    }
#if PRINT_COUNTS
    string tuple_string = stream.str();
    //tuple_counts[tuple_string]++;
    sorted_tuples.push_back(tuple_string);
#else
    out << std::endl;
#endif
}


void PrintNode(ITrieIterator<int>& trie_iterator, int printing_depth, ostream& out, int current_depth, vector<int>& current_tuple)
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


void TrieIteratorPrinter::Print(ITrieIterator<int>& trie_iterator, int printing_depth, ostream& out)
{
    // Print the trie contents in-order
    vector<int> current_tuple;
    PrintNode(trie_iterator, printing_depth, out, 0, current_tuple);
#if PRINT_COUNTS
//    for (map<string, int>::iterator it = tuple_counts.begin(); it != tuple_counts.end(); ++it)
//    {
//        out << it->first << "[" << it->second << "]" << std::endl;
//    }

    sort(sorted_tuples.begin(), sorted_tuples.end());
    for (vector<string>::iterator it = sorted_tuples.begin(); it != sorted_tuples.end(); ++it)
    {
        out << *it << std::endl;
    }
#endif
}

} // namespace uk_ac_ox_cs_c875114
