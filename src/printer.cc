#include <algorithm>
#include <vector>
#include "../include/printer.h"

namespace uk_ac_ox_cs_c875114
{

using std::string;
using std::vector;
using std::ostream;
using std::ostringstream;


void Printer::Print(Relation& relation, std::ostream& out)
{
    int tuple_size = relation.attribute_names.size();
    for (vector<int*>::iterator it = relation.data.begin(); it != relation.data.end(); ++it)
    {
        PrintTuple(*it, tuple_size, ',', out);
    }
}


void Printer::Print(ITrieIterator<int>& trie_iterator, ostream& out)
{
    // Print the trie contents in-order
    int tuple_size = trie_iterator.Arity();
    int* current_tuple = new int[tuple_size];

    PrintNode(trie_iterator, tuple_size, 0, current_tuple, out);

    delete[] current_tuple;
}


void Printer::PrintNode(ITrieIterator<int>& trie_iterator, int printing_depth, int current_depth, int* current_tuple, ostream& out)
{
    if (trie_iterator.Open() == kFail)
    {
        if (current_depth == printing_depth)
        {
            PrintTuple(current_tuple, printing_depth, ',', out);
        }

        return;
    }

    do
    {
        trie_iterator.Key(&current_tuple[current_depth]);

        PrintNode(trie_iterator, printing_depth, current_depth + 1, current_tuple, out);
    }
    while (trie_iterator.Next() == kOK);

    trie_iterator.Up();
}


inline void Printer::PrintTuple(int* current_tuple, int tuple_size, char separator, ostream& out)
{
    for (int i = 0; i < tuple_size; i++)
    {
        out << current_tuple[i] << separator;
    }

    out << std::endl;
}

} /* namespace uk_ac_ox_cs_c875114 */
