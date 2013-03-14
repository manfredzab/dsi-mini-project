#ifndef TRIE_ITERATOR_PRINTER_H_
#define TRIE_ITERATOR_PRINTER_H_

#include <ostream>
#include "trie_iterator.h"

class TrieIteratorPrinter
{
    public:
        static void Print(ITrieIterator& trie_iterator, int printing_depth, std::ostream& out);
};

#endif /* TRIE_ITERATOR_PRINTER_H_ */
