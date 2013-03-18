#ifndef TRIE_ITERATOR_PRINTER_H_
#define TRIE_ITERATOR_PRINTER_H_

#include <ostream>
#include "trie_iterator_interface.h"

#include <map>
#include <string>

namespace uk_ac_ox_cs_c875114
{

class TrieIteratorPrinter
{
    public:
        static void Print(ITrieIterator& trie_iterator, int printing_depth, std::ostream& out);
};

} // namespace uk_ac_ox_cs_c875114

#endif /* TRIE_ITERATOR_PRINTER_H_ */
