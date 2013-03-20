#ifndef PRINTER_H_
#define PRINTER_H_

#include <map>
#include <vector>
#include <string>
#include <ostream>
#include <iostream>

#include "relation.h"
#include "trie_iterator.h"

namespace uk_ac_ox_cs_c875114
{

class Printer
{
    public:
        static void PrintSorted(Relation& relation, std::ostream& out = std::cout);
        static void PrintSorted(ITrieIterator<int>& trie_iterator, std::ostream& out = std::cout);

    private:
        static void        PrintNode(ITrieIterator<int>& trie_iterator, int printing_depth, int current_depth, std::vector<int>& current_tuple);
        static std::string TupleToString(std::vector<int>& current_tuple, char separator);
        static std::string TupleToString(int* current_tuple, int tuple_size, char separator);
        static void        SortAndPrintTuples(std::ostream& out = std::cout);

        static std::vector<std::string> sorted_tuples;
};

} // namespace uk_ac_ox_cs_c875114

#endif /* PRINTER_H_ */
