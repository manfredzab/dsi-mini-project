#ifndef BINARY_SEARCH_TREE_TRIE_ITERATOR_H_
#define BINARY_SEARCH_TREE_TRIE_ITERATOR_H_

#include <stack>
#include "interface_trie_iterator.h"
#include "relation.h"
#include "linear_iterator.h"

namespace c875114
{

/**
 * Binary search tree wrapper, providing a trie iterator interface. Largely based on
 * the BTreeTrieIterator class by Todd L Veldhuizen.
 */
class BinarySearchTreeTrieIterator : public virtual ITrieIterator<int>
{
    public:
        BinarySearchTreeTrieIterator(const Relation& relation);
        virtual ~BinarySearchTreeTrieIterator();

        virtual Status Init();
        virtual Status Open();
        virtual Status Up();
        virtual Status Key(int* out_key);
        virtual Status Multiplicity(int* out_multiplicity);
        virtual Status Next();
        virtual bool   AtEnd();

        virtual Status Seek(int seek_key);

        virtual int Arity();

    private:
        void UpdateState();
        int  MatchDepth(int* first_tuple, int* second_tuple);

        const int kArity;                       /**< Trie arity */

        int                   depth;            /**< Trie depth. */
        LinearIterator        linear_iterator;  /**< Underlying linear iterator, based on a binary search tree. */
        int*                  tuple_state;      /**< Current path through the trie. */
        bool                  at_end;           /**< "At end" flag. */

        std::stack<TreeNode*> tree_node_stack;  /**< Stack of TreeNode pointers, used at Open and Up calls. */
        std::stack<bool>      at_end_stack;     /**< Stack of "At end" flags, used at Open and Up calls. */
};

} /* namespace c875114 */
#endif /* BINARY_SEARCH_TREE_TRIE_ITERATOR_H_ */
