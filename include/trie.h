#ifndef TRIE_H_
#define TRIE_H_

#include <vector>
#include "relation.h"

struct TrieNode
{
    public:
        TrieNode*                                  parent;
        int                                        key;
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

#endif /* TRIE_H_ */
