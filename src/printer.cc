#include <algorithm>
#include <vector>
#include <sstream>
#include "../include/printer.h"

namespace uk_ac_ox_cs_c875114
{

using std::string;
using std::vector;
using std::map;
using std::ostream;
using std::ostringstream;

void Printer::Print(Relation& relation, std::ostream& out)
{
    int tuple_size = relation.attribute_names.size();
    for (vector<Tuple>::iterator it = relation.data.begin(); it != relation.data.end(); ++it)
    {
        for (int i = 0; i < it->multiplicity; i++)
        {
            out << TupleToString(it->key, tuple_size, ',') << std::endl;
        }
    }
}


void Printer::Print(ITrieIterator<int>& trie_iterator, ostream& out)
{
    // Print the trie contents in-order
    vector<int> current_tuple;
    PrintNode(trie_iterator, trie_iterator.Arity(), 0, current_tuple, out);
}


void Printer::PrintNode(ITrieIterator<int>& trie_iterator, int printing_depth, int current_depth, vector<int>& current_tuple, ostream& out)
{
    if (trie_iterator.Open() == kFail)
    {
        if (current_depth == printing_depth)
        {
            out << TupleToString(current_tuple, ',') << std::endl;
        }

        return;
    }

    int current_node_key;
    do
    {
        trie_iterator.Key(&current_node_key);

        current_tuple.push_back(current_node_key);

        PrintNode(trie_iterator, printing_depth, current_depth + 1, current_tuple, out);

        current_tuple.pop_back();
    }
    while (trie_iterator.Next() == kOK);

    trie_iterator.Up();
}


string Printer::TupleToString(int* current_tuple, int tuple_size, char separator)
{
    ostringstream stream;

    for (int i = 0; i < tuple_size; i++)
    {
        stream << current_tuple[i] << separator;
    }

    return stream.str();
}


string Printer::TupleToString(vector<int>& current_tuple, char separator)
{
    ostringstream stream;

    for (vector<int>::iterator it = current_tuple.begin(); it != current_tuple.end(); ++it)
    {
        stream << *it << separator;
    }

    return stream.str();
}

} /* namespace uk_ac_ox_cs_c875114 */
