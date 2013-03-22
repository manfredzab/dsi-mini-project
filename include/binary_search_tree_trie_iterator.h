#ifndef BINARY_SEARCH_TREE_TRIE_ITERATOR_H_
#define BINARY_SEARCH_TREE_TRIE_ITERATOR_H_

#include <stack>
#include "interface_trie_iterator.h"
#include "relation.h"
#include "linear_iterator.h"

namespace uk_ac_ox_cs_c875114
{

/*
 * A wrapper class that takes a binary search tree and provides a trie iterator interface.
 * Largely based on the BTreeTrieIterator class by Todd Veldhuizen.
 */
class BinarySearchTreeTrieIterator : public virtual ITrieIterator<int>
{
    public:
        BinarySearchTreeTrieIterator(const Relation& relation);
        virtual ~BinarySearchTreeTrieIterator();

        /**
         * Initializes the underlying linear iterator. This method must be called before calling any other
         * method of the iterator.
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Init();


        /**
         * Positions the trie iterator at the first child of the current node.
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Open();

        /**
         * Positions the trie iterator at the parent node.
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Up();

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
         * Moves the trie iterator to the next element in same level (belonging to the same parent).
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Next();

        /**
         * Checks if the trie iterator is positioned at the last child of the parent node.
         * @returns true if the iterator is positioned at the last element, false otherwise.
         */
        virtual bool AtEnd();

        /**
         * Moves the trie iterator to the element which is i) in the same level, ii) belongs to the
         * same parent, and iii) is a least upper bound (LUB) for the seek key.
         * @param seek_key Seek key.
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Seek(int seek_key);

        /**
         * Returns the arity (maximum depth) of the trie.
         * @returns the arity (maximum depth) of the trie.
         */
        virtual int Arity();

    private:
        /**
         * Updates the state of the trie iterator (depth counter and "at end" flag).
         */
        void UpdateState();

        /**
         * Calculates the depth until which the tuples match completely (i.e. the longest
         * common prefix).
         * @param first_tuple Pointer to the first tuple.
         * @param second_tuple Pointer to the second tuple.
         * @returns Match depth (longest common prefix) for both tuples.
         */
        int MatchDepth(int* first_tuple, int* second_tuple);

        const int kArity; /**< Trie arity */

        int                   depth;            /**< Trie depth. */
        LinearIterator        linear_iterator;  /**< Underlying linear iterator, based on a binary search tree. */
        int*                  tuple_state;      /**< Current path through the trie. */
        bool                  at_end;           /**< "At end" flag. */

        std::stack<TreeNode*> tree_node_stack;  /**< Stack of TreeNode pointers, used at Open and Up calls. */
        std::stack<bool>      at_end_stack;     /**< Stack of "At end" flags, used at Open and Up calls. */
};

} /* namespace uk_ac_ox_cs_c875114 */
#endif /* BINARY_SEARCH_TREE_TRIE_ITERATOR_H_ */
