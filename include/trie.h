#ifndef TRIE_H_
#define TRIE_H_

#include <vector>
#include "relation.h"

namespace c875114
{

/**
 * Holder of internal trie node data: pointer to the parent, node key, node multiplicity,
 * a list of children trie nodes and the pointer to the currently open child.
 */
struct TrieNode
{
    TrieNode*                                  parent;
    int                                        key;
    int                                        multiplicity;
    std::vector<TrieNode*>                     children;
    typename std::vector<TrieNode*>::iterator  current_child;
};

/**
 * Trie data structure. Builds a trie for a given relation in the order of relation's
 * attributes.
 */
class Trie
{
    public:
        Trie(const Relation& relation);
        virtual ~Trie();

        /**
         * Compares two trie nodes by keys.
         * @param first First node.
         * @param second Second node.
         * @returns true if the key of the first node is strictly smaller than
         *          the key of the second node, false otherwise.
         */
        static bool CompareTrieNodeKeys(TrieNode* first, TrieNode* second)
        {
            return (first->key < second->key);
        }

        TrieNode root; /**< Root node of the trie. */

    private:
        void Insert(const int* tuple);

        int trie_depth; /**< Depth of the trie. */
};

} /* namespace c875114 */

#endif /* TRIE_H_ */
