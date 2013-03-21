#ifndef TRIE_H_
#define TRIE_H_

#include <vector>
#include "relation.h"

namespace uk_ac_ox_cs_c875114
{

struct TrieNode
{
    TrieNode*                                  parent;
    int                                        key;
    int                                        multiplicity;
    std::vector<TrieNode*>                     children;
    typename std::vector<TrieNode*>::iterator  current_child;
};

bool CompareTrieNodeKeys(TrieNode* first, TrieNode* second);

class Trie
{
    public:
        Trie(const Relation& relation);
        virtual ~Trie();

        TrieNode root;
    private:
        void Insert(const int* tuple);

        int trie_depth;
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* TRIE_H_ */
