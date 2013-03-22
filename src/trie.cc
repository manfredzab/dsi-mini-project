#include <algorithm>
#include "../include/trie.h"
#include "../include/simple_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;

Trie::Trie(const Relation& relation)
{
    trie_depth = relation.attribute_names.size();

    root.parent = NULL;
    root.key = 0;
    root.multiplicity = 1;
    root.current_child = root.children.begin();

    // Build the trie
    SimpleIterator relation_iterator(relation);

    Tuple current_tuple;
    while (!relation_iterator.AtEnd())
    {
        relation_iterator.Key(&current_tuple.key);
        relation_iterator.Next();

        Insert(current_tuple);
    }
}

Trie::~Trie()
{
    vector<TrieNode*> nodes_to_delete;

    nodes_to_delete.insert(nodes_to_delete.begin(), root.children.begin(), root.children.end());
    while (!nodes_to_delete.empty())
    {
        TrieNode* current_node = nodes_to_delete.back();
        nodes_to_delete.pop_back();

        nodes_to_delete.insert(nodes_to_delete.end(), current_node->children.begin(), current_node->children.end());

        delete current_node;
    }
}


void Trie::Insert(const Tuple& tuple)
{
    TrieNode* currentNode = &this->root;
    for (int i = 0; i < this->trie_depth; i++)
    {
        // Find the entry to insert in the children list
        TrieNode* trie_node_to_insert = new TrieNode();
        trie_node_to_insert->key = tuple.key[i];

        vector<TrieNode*>::iterator insert_position_node = lower_bound(currentNode->children.begin(),
                                                                       currentNode->children.end(),
                                                                       trie_node_to_insert,
                                                                       CompareTrieNodeKeys);

        // If the node with this key is not present in the children list, finish initializing members
        // and insert it.
        if (insert_position_node == currentNode->children.end())
        {
            trie_node_to_insert->parent = currentNode;
            trie_node_to_insert->multiplicity = 1;
            trie_node_to_insert->current_child = trie_node_to_insert->children.begin();

            insert_position_node = currentNode->children.insert(insert_position_node, trie_node_to_insert);
        }
        else
        {
            // Node with this key already exists in the trie, and the new node is unnecessary
            delete trie_node_to_insert;

            // However, if we were at the leaf level, increase the leaf's multiplicity
            if (i == this->trie_depth - 1)
            {
                (*insert_position_node)->multiplicity++;
            }
        }

        currentNode = *insert_position_node;
    }
}
} /* namespace uk_ac_ox_cs_c875114 */
