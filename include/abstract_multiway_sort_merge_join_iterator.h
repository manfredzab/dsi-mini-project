#ifndef ABSTRACT_MULTIWAY_SORT_MERGE_JOIN_ITERATOR_H_
#define ABSTRACT_MULTIWAY_SORT_MERGE_JOIN_ITERATOR_H_

#include <vector>
#include "interface_iterator.h"
#include "interface_trie_iterator.h"
#include "status.h"

namespace c875114
{

/**
 * Basis for a generic multi-way sort-merge join iterator.
 *
 * To get an instance of a multi-way sort-merge join iterator, PositionCurrentIteratorAtKey method
 * needs to be implemented. E.g. in a regular multi-way sort merge join, PositionCurrentIteratorAtKey
 * is implemented as a tuple-by-tuple scan in the current trie iterator level. In the leapfrog join,
 * this method is implemented as an efficient \f$O(\log N)\f$ (amortized \f$O(1 + \log N/m)\f$) seek in the current
 * trie iterator level.
 *
 * Trie iterator handling is largely based on the leapfrog join iterator as proposed by Todd L Veldhuizen in
 * "Leapfrog Triejoin: A Simple, Worst-Case Optimal Join Algorithm", LogicBlox Technical Report LB1201, December 2012.
 */
template <class TTrieIterator>
class AbstractMultiwaySortMergeJoinIterator : public virtual IIterator<int>
{
    public:
        AbstractMultiwaySortMergeJoinIterator(std::vector<TTrieIterator*>& iterators);
        virtual ~AbstractMultiwaySortMergeJoinIterator() { };

        virtual Status Init();
        virtual Status Key(int* out_key);
        virtual Status Multiplicity(int* out_multiplicity);
        virtual Status Next();
        virtual bool   AtEnd();

    protected:
        /**
         * An abstract method to find the least upper bound (LUB) for a given key
         * at the current trie iterator.
         * @param key Key for which the LUB should be found.
         */
        virtual void PositionCurrentIteratorAtKey(int key) = 0;

        virtual void Search();

        std::vector<TTrieIterator*>& iterators; /**< A list of trie iterators of the relations that
                                                     participate in this multiway join. */
        int  current_iterator_index;            /**< Current iterator index. */

        bool at_end;                            /**< "At-end" flag. */
        int  key;                               /**< Current key */
        int  min_key;                           /**< Current minimum key (used in Search()). */
        int  max_key;                           /**< Current maximum key (used in Search()). */
        int  key_multiplicity;                  /**< Current key multiplicity. */
};

} /* namespace c875114 */

#endif /* ABSTRACT_MULTIWAY_SORT_MERGE_JOIN_ITERATOR_H_ */
