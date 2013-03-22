/*
 * Largely based on the BTreeTrieIterator class by Todd Veldhuizen.
 */

#ifndef BINARY_SEARCH_TREE_TRIE_ITERATOR_H_
#define BINARY_SEARCH_TREE_TRIE_ITERATOR_H_

#include <stack>
#include "interface_trie_iterator.h"
#include "relation.h"
#include "linear_iterator.h"

namespace uk_ac_ox_cs_c875114
{

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
        virtual int    Arity();

        virtual Status Seek(int seek_key);

    private:
        void UpdateState();
        int MatchDepth(int* first_tuple, int* second_tuple);

        const int kArity;

        int                   depth;
        LinearIterator        linear_iterator;
        int*                  tuple_state;
        bool                  at_end;

        std::stack<TreeNode*> tree_node_stack;
        std::stack<bool>      at_end_stack;
};

} /* namespace uk_ac_ox_cs_c875114 */
#endif /* BINARY_SEARCH_TREE_TRIE_ITERATOR_H_ */
