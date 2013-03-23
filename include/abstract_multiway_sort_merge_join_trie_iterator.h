#ifndef ABSTRACT_MULTIWAY_SORT_MERGE_JOIN_TRIE_ITERATOR_H_
#define ABSTRACT_MULTIWAY_SORT_MERGE_JOIN_TRIE_ITERATOR_H_

#include <map>
#include <string>
#include <vector>

#include "relation.h"
#include "query.h"
#include "status.h"
#include "interface_trie_iterator.h"
#include "interface_iterator.h"

namespace c875114
{

/**
 * Basis for a generic multi-way sort-merge join trie iterator. For each join variable X it uses join iterators (of
 * generic TJoinIterator type) over trie iterators (of generic TTrieIterator type) on relations containing X, to
 * produce a non-materialized trie over the resulting relation.
 *
 * For example, a multi-way sort-merge join trie iterator instantiates TTrieIterator to TrieTrieIterator, and
 * TJoinIterator to MultiwaySortMergeJoinIterator. A leapfrog join trie iterator instantiates TTrieIterator to
 * BinarySearchTreeTrieIterator, and TJoinIterator to LeapfrogJoinIterator.
 *
 * Both of these algorithms also provide implementations of CreateTrieIteratorForRelation and CreateJoinIteratorForTrieIterators
 * methods to create these iterators.
 */
template <class TTrieIterator, class TJoinIterator>
class AbstractMultiwaySortMergeJoinTrieIterator : public virtual ITrieIterator<int>
{
    public:
        AbstractMultiwaySortMergeJoinTrieIterator(const std::map<std::string, Relation*>& relations, const Query& query);
        virtual ~AbstractMultiwaySortMergeJoinTrieIterator();

        virtual Status Init();
        virtual Status Open();
        virtual Status Up();
        virtual Status Key(int* out_key);
        virtual Status Multiplicity(int* out_multiplicity);
        virtual Status Next();
        virtual bool   AtEnd();
        virtual int    Arity();

    protected:
        virtual bool AtRoot();

        /**
         * An abstract method that creates a trie iterator for a given relation.
         * @param relation Input relation.
         * @returns A pointer to the trie iterator for a given relation.
         */
        virtual TTrieIterator* CreateTrieIteratorForRelation(const Relation& relation) = 0;

        /**
         * An abstract method that creates a join iterator for given relation trie iterators.
         * @param trie_iterators A reference to the list of trie iterators.
         * @returns A pointer to the join iterator for given trie iterators.
         */
        virtual TJoinIterator* CreateJoinIteratorForTrieIterators(std::vector<TTrieIterator*>& trie_iterators) = 0;

        int depth;                                                                 /**< Current trie depth. */

        std::vector<int> key_multiplicity_stack;                                   /**< Key multiplicities along the current path in the trie. */

        int number_of_join_attributes;                                             /**< Number of join attributes. */
        int number_of_result_attributes;                                           /**< Result tuple size. */

        std::map<std::string, TTrieIterator*>       trie_iterator_for_relation;    /**< A dictionary of iterators for a particular relation (indexed by name). */
        std::map<int, std::vector<TTrieIterator*> > trie_iterators_for_depth;      /**< A dictionary of iterators for a particular attribute (indexed by attribute's position in the output relation). */
        std::map<int, TJoinIterator*>               join_iterator_for_depth;       /**< A map between an attribute and an associated join iterator (indexed by attribute's position in the result relation). */

    private:
        const std::map<std::string, Relation*>& relations;                         /**< Input relations. */
        const Query&                            query;                             /**< Input query. */
};

} /* namespace c875114 */

#endif /* ABSTRACT_MULTIWAY_SORT_MERGE_JOIN_TRIE_ITERATOR_H_ */
