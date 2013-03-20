#include <algorithm>
#include <vector>
#include <list>
#include <sstream>
#include "../include/printer.h"

namespace uk_ac_ox_cs_c875114
{

using std::string;
using std::vector;
using std::list;
using std::map;
using std::ostream;
using std::ostringstream;

vector<string> Printer::sorted_tuples;

void Printer::PrintSorted(Relation& relation, std::ostream& out)
{
    sorted_tuples.clear();

    int tuple_size = relation.attribute_names.size();
    for (list<int*>::iterator it = relation.data.begin(); it != relation.data.end(); ++it)
    {
        sorted_tuples.push_back(TupleToString(*it, tuple_size, ','));
    }

    SortAndPrintTuples(out);
}


void Printer::PrintSorted(ITrieIterator<int>& trie_iterator, ostream& out)
{
    sorted_tuples.clear();

    // Print the trie contents in-order
    vector<int> current_tuple;
    PrintNode(trie_iterator, trie_iterator.Depth(), 0, current_tuple);

    SortAndPrintTuples(out);
}


void Printer::SortAndPrintTuples(std::ostream& out)
{
    sort(sorted_tuples.begin(), sorted_tuples.end());
    for (vector<string>::iterator it = sorted_tuples.begin(); it != sorted_tuples.end(); ++it)
    {
        out << *it << std::endl;
    }
}


void Printer::PrintNode(ITrieIterator<int>& trie_iterator, int printing_depth, int current_depth, vector<int>& current_tuple)
{
    if (trie_iterator.Open() == kFail)
    {
        if (current_depth == printing_depth)
        {
            sorted_tuples.push_back(TupleToString(current_tuple, ','));
        }

        return;
    }

    int current_node_key;
    do
    {
        trie_iterator.Key(&current_node_key);

        current_tuple.push_back(current_node_key);

        PrintNode(trie_iterator, printing_depth, current_depth + 1, current_tuple);

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

} // namespace uk_ac_ox_cs_c875114
