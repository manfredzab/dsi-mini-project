#ifndef TRIE_TRIE_ITERATOR_H_
#define TRIE_TRIE_ITERATOR_H_

#include "interface_trie_iterator.h"
#include "trie.h"

namespace uk_ac_ox_cs_c875114
{

class TrieTrieIterator : public virtual ITrieIterator<int>
{
    public:
        TrieTrieIterator(const Relation& relation);
        virtual ~TrieTrieIterator();

        virtual Status Init();
        virtual Status Open();
        virtual Status Up();
        virtual Status Key(int* out_key);
        virtual Status Multiplicity(int* out_multiplicity);
        virtual Status Next();
        virtual bool   AtEnd();
        virtual int    Arity();

        /**
         * An inline trie iterator comparator, which compares tries by their current keys using
         * < (less than) relation on integers.
         * @param first  First trie iterator to compare.
         * @param second Second trie iterator to compare.
         * @returns true, if the current key at the first trie iterator is strictly less than the
         *          current key at the second trie iterator, and false otherwise.
         */
        static bool CompareTrieIteratorsByKeys(ITrieIterator<int>* first, ITrieIterator<int>* second)
        {
            int first_result, second_result;
            first->Key(&first_result); second->Key(&second_result);

            return (first_result < second_result);
        }

    protected:
        virtual bool AtRoot();

        const int kArity;

        Trie*     trie;
        TrieNode* current_node;
        int       current_node_multiplicity;
        bool      at_end;
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* TRIE_TRIE_ITERATOR_H_ */
