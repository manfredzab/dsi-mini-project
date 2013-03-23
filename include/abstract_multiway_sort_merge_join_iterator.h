#ifndef ABSTRACT_MULTIWAY_SORT_MERGE_JOIN_ITERATOR_H_
#define ABSTRACT_MULTIWAY_SORT_MERGE_JOIN_ITERATOR_H_

#include <vector>
#include "interface_iterator.h"
#include "interface_trie_iterator.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

/**
 * An abstract class that serves as a basis for generic multiway sort-merge join iterator.
 * To get an instance of a multiway sort-merge join iterator, PositionCurrentIteratorAtKey method
 * needs to be implemented. E.g. in a regular multi-way sort merge join, PositionCurrentIteratorAtKey
 * is implemented as a tuple-by-tuple scan in the current trie iterator level. In the leapfrog join,
 * this method is implemented as an efficient O(logN) (amortized O(1 + log N/m)) seek in the current
 * trie iterator level.
 */
template <class TTrieIterator>
class AbstractMultiwaySortMergeJoinIterator : public virtual IIterator<int>
{
    public:
        AbstractMultiwaySortMergeJoinIterator(std::vector<TTrieIterator*>& iterators);
        virtual ~AbstractMultiwaySortMergeJoinIterator() { };

        /**
         * Initializes the iterator. This method must be called before calling any other method
         * of the iterator.
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Init();

        /**
         * Returns the key at a current position of the iterator.
         * @param out_key A pointer to the memory location where the key should be
         *                stored.
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Key(int* out_key);

        /**
         * Returns the multiplicity of the key at a current position of the iterator.
         * @param out_multiplicity A pointer to the memory location where the multiplicity
         *                         should be stored.
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Multiplicity(int* out_multiplicity);

        /**
         * Moves the join iterator to the next element in the trie iterator insersection.
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Next();

        /**
         * Checks if the join iterator is positioned at the last element in the trie
         * iterator intersection.
         * @returns true if the iterator is at the last element, false otherwise.
         */
        virtual bool AtEnd();

    protected:
        /**
         * An abstract method to find the least upper bound (LUB) for a given key
         * at the current trie iterator.
         * @param key Key for which the LUB should be found.
         */
        virtual void PositionCurrentIteratorAtKey(int key) = 0;

        /**
         * Positions all trie iterators at the next element of the iterator key
         * intersection.
         */
        virtual void Search();

        std::vector<TTrieIterator*>& iterators; /**< A list of trie iterators of the relations that
                                                     participate in this multiway join. */
        int  current_iterator_index;            /**< Current iterator index. */

        bool at_end;           /**< "At-end" flag. */
        int  key;              /**< Current key */
        int  min_key;          /**< Current minimum key (used in Search()). */
        int  max_key;          /**< Current maximum key (used in Search()). */
        int  key_multiplicity; /**< Current key multiplicity. */
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* ABSTRACT_MULTIWAY_SORT_MERGE_JOIN_ITERATOR_H_ */
