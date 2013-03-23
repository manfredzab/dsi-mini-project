#ifndef PRINTER_H_
#define PRINTER_H_

#include <string>
#include <ostream>
#include <iostream>

#include "relation.h"
#include "interface_trie_iterator.h"

namespace c875114
{

/**
 * Relation/trie printer into a given output stream. Tries are printed in a depth-first search manner.
 */
class Printer
{
    public:
        static void Print(Relation& relation, std::ostream& out = std::cout);
        static void Print(ITrieIterator<int>& trie_iterator, std::ostream& out = std::cout);

    private:
        static void PrintNode(ITrieIterator<int>& trie_iterator, int printing_depth, int current_depth, int* current_tuple, std::ostream& out);
        static void PrintTuple(int* current_tuple, int tuple_size, char separator, std::ostream& out);
};

} /* namespace c875114 */

#endif /* PRINTER_H_ */
