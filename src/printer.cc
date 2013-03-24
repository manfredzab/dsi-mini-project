#include <algorithm>
#include <vector>
#include "../include/printer.h"

namespace c875114
{

using std::string;
using std::vector;
using std::ostream;
using std::ostringstream;

/**
 * Prints a given relation to a given output stream
 * @param relation Relation to be printed.
 * @param out      Output stream to which the relation should be printed.
 */
void Printer::Print(Relation& relation, std::ostream* out)
{
    int tuple_size = relation.attribute_names.size();
    for (vector<int*>::iterator it = relation.data.begin(); it != relation.data.end(); ++it)
    {
        PrintTuple(*it, tuple_size, ',', *out);
    }
}

/**
 * Prints a given trie to a given output stream
 * @param trie_iterator Iterator over a trie to be printed.
 * @param out           Output stream to which the relation should be printed.
 */
void Printer::Print(ITrieIterator<int>& trie_iterator, ostream* out)
{
    // Print the trie contents in-order
    int tuple_size = trie_iterator.Arity();
    int* current_tuple = new int[tuple_size];

    PrintNode(trie_iterator, tuple_size, 0, current_tuple, out);

    delete[] current_tuple;
}

/**
 * Recursively prints trie iterator nodes, iterating over a trie in a depth-first manner.
 * @param trie_iterator  Trie iterator.
 * @param printing_depth Depth at which tuples should be printed.
 * @param current_tuple  Current tuple build while traversing the trie (i.e. path over the trie).
 * @param out            Output stream where trie should be printed.
 */
void Printer::PrintNode(ITrieIterator<int>& trie_iterator, int printing_depth, int current_depth, int* current_tuple, ostream* out)
{
    // Iterate depth-first
    if (trie_iterator.Open() == kFail)
    {
        if ((current_depth == printing_depth) && (out != NULL))
        {
            PrintTuple(current_tuple, printing_depth, ',', *out);
        }

        return;
    }

    do // Scan the siblings
    {
        trie_iterator.Key(&current_tuple[current_depth]);

        PrintNode(trie_iterator, printing_depth, current_depth + 1, current_tuple, out);
    }
    while (trie_iterator.Next() == kOK);

    // Backtrack
    trie_iterator.Up();
}

/**
 * Prints the tuple to a given output stream, separating the attributes with a given separator
 * character.
 * @param current_tuple Pointer to a tuple to be printed.
 * @param tuple_size    Tuple size (number of attributes).
 * @param separator     Separator character that should be used to separate the attributes.
 * @param out           Output stream where the tuple should be printed.
 */
inline void Printer::PrintTuple(int* current_tuple, int tuple_size, char separator, ostream& out)
{
    for (int i = 0; i < tuple_size; i++)
    {
        out << current_tuple[i] << separator;
    }

    out << std::endl;
}

} /* namespace c875114 */
